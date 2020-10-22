#ifndef WAVE_H
#define WAVE_H

/* RIFF WAVE file format */

#include "filter.h"
#include <stdint.h>
#include <stdio.h>

struct wave {
    char     riff_tag[4];   /* RIFF chunk tag */
    uint32_t riff_size;     /* size of file (minus 8 bytes) */
    char     wave_tag[4];   /* WAVE chunk tag */
    char     fmt_tag[4];    /* 'fmt ' chunk tag */
    uint32_t fmt_size;      /* size of data format */
    uint16_t format;        /* format type 1-PCM, 3-FLOAT */
    uint16_t channels;      /* # of channels */
    uint32_t samplerate;    /* sample rate (fs) */
    uint32_t byterate;      /* byte rate = fs * channels * bitspersample / 8 */
    uint16_t blockalign;    /* block align = channels * bitspersample / 8 */
    uint16_t bitspersample; /* 8 bits or 16 bits */
    char     data_tag[4];   /* data chunk tag */
    uint32_t data_size;     /* size of data */
};

/* read the WAVEfmt RIFF header */
long wave_read_header(struct wave *fmt, const char *tag, FILE *fp);

/* write the WAVEfmt RIFF header */
long wave_write_header(const struct wave *fmt, FILE *fp);

/* print summary of the WAVEfmt RIFF header to stdout */
void wave_print_header(const struct wave *fmt);

/* dump a summary of the wav file to stdout */
int wave_dump(const char *filename);

/* sample by sample process wav file */
int wave_filter(const char *infile, const char *outfile,
                   filter_func *f, void *state, int format, double t);

#define WAVE_PCM     1
#define WAVE_FLOAT   3
#define WAVE_ALAW    6
#define WAVE_uLAW    7

#endif /* WAVE_H */
