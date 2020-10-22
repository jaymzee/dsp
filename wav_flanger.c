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
    struct delay_state *delay;
};

float flanger_procsamp(float x, void *state)
{
    struct flanger *fl = state;
    struct delay_state *delay = fl->delay;
    const int N = delay->N;
    double y;
    double n;

    n = (N-1) * (0.5 * cos(2 * PI * fl->rate * fl->phase) + 0.5);

    *delay_w0(delay) = x;

    y = 0.5 * delay_w(delay, N / 2) + 0.5 * delay_w(delay, n);

    delay_dec(delay);
    fl->phase += 1.0 / 44100.0;

    return y;
}

int main(int argc, char *argv[])
{
    struct flanger fl;
    int rv;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavflanger infile outfile\n");
        return EXIT_FAILURE;
    }

    fl.rate = 0.125;
    fl.phase = 0.0;
    fl.delay = delay_create(200);
    rv = wave_filter(argv[1], argv[2], flanger_procsamp, &fl, WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
