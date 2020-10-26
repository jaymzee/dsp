#include "CanonicalFilter.h"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>

dsp::CanonicalFilter f({0.2, 0.2, 0.2}, {1.0, 0.3, 0.3});

int main(int argc, char *argv[])
{
    const char *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavCanFilt infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    return WaveFilter(infile, outfile, &f, WAVE_PCM, 0.0);
}
