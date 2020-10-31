#include "BiQuadFilter.h"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>

dsp::BiQuadFilter f({0.00425, 0.0, -0.00425}, {1.0, -1.98, 0.991});

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return EXIT_FAILURE;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];

    return WaveFilter(infile, outfile, &f, WAVE_FLOAT, 0.0);
}
