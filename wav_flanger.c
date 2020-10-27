#include "wave.h"
#include "fractional_delay.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

struct flanger
{
    double rate;
    double phase;
    struct fracdelay *delay;
};

double flanger_sample(struct flanger *f, double x)
{
    struct fracdelay *delay = f->delay;
    const int N = delay->N;
    double y;
    double n;

    n = (N-1) * (0.5 * cos(2 * PI * f->rate * f->phase) + 0.5);

    *fracdelay_w0(delay) = x;

    y = 0.5 * fracdelay_w(delay, N / 2) + 0.5 * fracdelay_w(delay, n);

    fracdelay_dec(delay);
    f->phase += 1.0 / 44100.0;

    return y;
}

int main(int argc, char *argv[])
{
    const char *infile, *outfile;
    struct flanger f;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    f.rate = 0.125;
    f.phase = 0.0;
    f.delay = fracdelay_create(200);

    return wave_filter(infile, outfile,
                       (filter_func)flanger_sample, &f, WAVE_PCM, 0.0);
}
