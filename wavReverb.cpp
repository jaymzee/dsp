#include "CircularFilter.h"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavReverb infile outfile\n");
        return EXIT_FAILURE;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];

    dsp::CircularFilter f(5000);
    f.b[1] = 0.4;
    f.b[3500] = 0.4;
    f.a[3000] = 0.6;

    return WaveFilter(infile, outfile, &f, WAVE_PCM, 2.0);
}
