#include "wave.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* helper for wave_read_header */
static long read_fmt(struct wave *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

    bytecount += fread(&fmt->fmt_size, 4, 1, fp) * 4;
    if (fmt->fmt_size >= 16) {
        bytecount += fread(&fmt->format, 2, 1, fp) * 2;
        bytecount += fread(&fmt->channels, 2, 1, fp) * 2;
        bytecount += fread(&fmt->samplerate, 4, 1, fp) * 4;
        bytecount += fread(&fmt->byterate, 4, 1, fp) * 4;
        bytecount += fread(&fmt->blockalign, 2, 1, fp) * 2;
        bytecount += fread(&fmt->bitspersample, 2, 1, fp) * 2;
    } else {
        fprintf(stderr,
                "%s: expected length of chunk fmt >= 16 bytes, got %d\n",
                fn, fmt->fmt_size);
    }
    if (bytecount < fmt->fmt_size + 4) {
        long skip = fmt->fmt_size + 4 - bytecount;
        fprintf(stderr,
                "%s: skipping extra %ld bytes at end of chunk fmt\n", 
                fn, skip);
        fseek(fp, skip, SEEK_CUR);
        bytecount += skip;
    }

    return bytecount;
}

/* helper for wave_read_header */
static long read_data(struct wave *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

    bytecount += fread(&fmt->data_size, 4, 1, fp) * 4;

    /* don't actually read the data.
       leave the file pointer right at the beginning of it
       since this is the last chunk */

    return bytecount;
}

/*
 * wave_read_header() - read the wave RIFF header
 * fmt: pointer to the format header structure to fill
 * fn:  filename (for better error messages)
 * fp:  the file to read it from
 *
 * Return: offset of the start of wave data on a successful read of format
 *         0 otherwise
 */
long wave_read_header(struct wave *fmt, const char *fn, FILE *fp)
{
    long bytecount = 0;

    bytecount += fread(fmt->riff_tag, 1, 4, fp);
    if (strncmp(fmt->riff_tag, "RIFF", 4) != 0) {
        fprintf(stderr,
                "%s: expected chunk RIFF, but got %.4s\n",
                fn, fmt->riff_tag);
        goto fail;
    }
    bytecount += fread(&fmt->riff_size, 4, 1, fp) * 4;
    bytecount += fread(fmt->wave_tag, 1, 4, fp);
    if (strncmp(fmt->wave_tag, "WAVE", 4) != 0) {
        fprintf(stderr,
                "%s: expected chunk WAVE, but got %.4s\n",
                fn, fmt->wave_tag);
        goto fail;
    }

    while (!feof(fp)) {
        /* read chunk tag and the chunk */
        char chunktag[4];
        bytecount += fread(chunktag, 1, 4, fp);
        if (strncmp(chunktag, "fmt ", 4) == 0) {
            strncpy(fmt->fmt_tag, chunktag, 4);
            bytecount += read_fmt(fmt, fn, fp);
        } else if (strncmp(chunktag, "data", 4) == 0) {
            strncpy(fmt->data_tag, chunktag, 4);
            bytecount += read_data(fmt, fn, fp);
            goto success;
        } else {
            /* ignore chunk */
            uint32_t chunksize;
            fprintf(stderr, "%s: ignoring chunk %.4s\n", fn, chunktag);
            bytecount += fread(&chunksize, 4, 1, fp) * 4;
            fseek(fp, chunksize, SEEK_CUR);
            bytecount += chunksize;
        }
    }

success:
    return bytecount;   /* SUCCESS */
fail:
    return 0;   /* FAILURE - could not parse header properly */
}

/*
 * wave_write_header() - write wave RIFF header to file
 * fmt: pointer to the format header struct to write
 *
 * Return: bytes written to file
 */
long wave_write_header(const struct wave *fmt, FILE *fp)
{
    return fwrite(fmt, sizeof(*fmt), 1, fp);
}

/*
 * wave_print_header() - print wave RIFF header to stdout
 * fmt: pointer to the format header structure to dump
 *
 * struct wave fmt;
 * FILE fp = fopen("audio.wav", "rb");
 * long seek = wave_read_header(&fmt, fp);
 * wave_print_header(&fmt);
 * ...
 * ... process audio
 * ...
 */
void wave_print_header(const struct wave *fmt)
{
    printf("file length: %u\n", fmt->riff_size + 8);
    printf("format: ");
    switch (fmt->format) {
    case WAVE_PCM:
        printf("PCM");
        break;
    case WAVE_FLOAT:
        printf("IEEE float");
        break;
    case WAVE_ALAW:
        printf("8 bit A-law");
        break;
    case WAVE_uLAW:
        printf("8 bit mu-law");
    default:
        printf("unknown %d", fmt->format);
        break;
    }
    printf("\n");
    printf("channels: %d\n", fmt->channels);
    printf("sample rate: %d\n", fmt->samplerate);
    printf("byte rate: %d\n", fmt->byterate);
    printf("block align: %d\n", fmt->blockalign);
    printf("bits per sample: %d\n", fmt->bitspersample);
    printf("data length (bytes): %d\n", fmt->data_size);
}

/*
 * wave_dump() - print wave RIFF header to stdout
 * filename: file to dump
 *
 * convenience procedure for writing a wav file dump utility
 *
 * Return: 0 on successful read of RIFF header
          -2 could not open file
          -3 could not parse file
 */
int wave_dump(const char *filename)
{
    FILE *fp;
    struct wave fmt;
    long data_seek_start;

    fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        return -2;
    }
    data_seek_start = wave_read_header(&fmt, filename, fp);
    if (!data_seek_start) {
        /* wave_read_header has already displayed a helpful error message */
        return -3;
    }
    fclose(fp);

    wave_print_header(&fmt);
    printf("data seek start: 0x%08lx\n", data_seek_start);

    return 0;
}

static double clamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}

static void filter_pcm2float(FILE *fpi, FILE *fpo,
                             filter_func f, void *state,
                             uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&samp16, 2, 1, fpi);
        x = samp16 / 32767.0;
        y = clamp(f(state, x), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(state, x), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
}

static void filter_pcm2pcm(FILE *fpi, FILE *fpo,
                           filter_func f, void *state,
                           uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&samp16, 2, 1, fpi);
        x = samp16 / 32767.0;
        y = clamp(f(state, x), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(state, x), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
}


static void filter_float2float(FILE *fpi, FILE *fpo,
                               filter_func f, void *state,
                               uint32_t Nin, uint32_t Nout)
{
    float x, y;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&x, 4, 1, fpi);
        y = clamp(f(state, x), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(state, x), -1.0, 1.0);
        fwrite(&y, 4, 1, fpo);
    }
}

static void filter_float2pcm(FILE *fpi, FILE *fpo,
                             filter_func f, void *state,
                             uint32_t Nin, uint32_t Nout)
{
    float x, y;
    int16_t samp16;
    uint32_t n = 0;

    while (n < Nin) {
        n += fread(&x, 4, 1, fpi);
        y = clamp(f(state, x), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
    while (n < Nout) {
        n++;
        x = 0.0;
        y = clamp(f(state, x), -1.0, 1.0);
        samp16 = (int)(32768.5 + 32767.0 * y) - 32768;
        fwrite(&samp16, 2, 1, fpo);
    }
}

/*
 * wave_filter() - sample by sample filter
 * infile: filename of input wav file
 * outfile: filename of output wav file
 * f: callback function for sample by sample processing
 * state: state to pass to sample processing function
 * format: WAVE_FLOAT or WAVE_PCM
 * t: length of time to run filter
 *
 * signal process infile to outfile (float)
 * t = 0.0 will make the output the same length as the input
 *
 * Return: 0 on success
 *         1 could not open file
 *         2 could not parse file
 *         4 unsupported file format
 */
int wave_filter(const char *infile, const char *outfile,
                filter_func f, void *state, int format, double t)
{
    FILE *fpi, *fpo;
    struct wave in, out;
    long data_offset;
    unsigned int Nin, Nout;

    fpi = fopen(infile, "rb");
    if (!fpi) {
        perror(infile);
        return 1;
    }
    fpo = fopen(outfile, "wb");
    if (!fpo) {
        perror(outfile);
        return 1;
    }
    data_offset = wave_read_header(&in, infile, fpi);
    if (!data_offset) {
        return 2;
    }
    if (in.channels != 1) {
        fprintf(stderr, "%s: number of channels must be 1\n", infile);
        return 4;
    }
    if (format != WAVE_PCM && format != WAVE_FLOAT) {
        fprintf(stderr, "unsupported output format %d\n", format);
        return 4;
    }

    out = in;
    Nin = in.data_size / in.blockalign;
    Nout = (t == 0.0) ? Nin : out.samplerate * t;
    out.format = format;
    out.fmt_size = 16;
    out.bitspersample = (format == WAVE_FLOAT) ? 32 : 16;
    out.blockalign = (format == WAVE_FLOAT) ? 4 : 2;
    out.byterate = out.blockalign * out.samplerate;
    out.data_size = Nout * out.blockalign;
    out.riff_size = out.data_size + 16 + 8 + 8 + 4;
    wave_write_header(&out, fpo);

    if (in.format == WAVE_PCM && in.bitspersample == 16) {
        if (out.format == WAVE_FLOAT)
            filter_pcm2float(fpi, fpo, f, state, Nin, Nout);
        else if (out.format == WAVE_PCM)
            filter_pcm2pcm(fpi, fpo, f, state, Nin, Nout);
        else
            goto fail;
    } else if (in.format == WAVE_FLOAT && in.bitspersample == 32) {
        if (out.format == WAVE_FLOAT)
            filter_float2float(fpi, fpo, f, state, Nin, Nout);
        else if (out.format == WAVE_PCM)
            filter_float2pcm(fpi, fpo, f, state, Nin, Nout);
        else
            goto fail;
    } else {
        goto fail;
    }

    fclose(fpi);
    fclose(fpo);
    return 0;

fail:
    fprintf(stderr, "%s: filter from %d to %d unsupported\n",
            infile, in.format, out.format);
    return 4;
}
