#include "directform.h"
#include "wave.hpp"
#include <cstdio>
#include <cstdlib>

dsp::DirectForm1 f{{1.0}, {1.0, 0.5}};

int main(int argc, char *argv[])
{
    const char *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavCanFilt infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    return FilterWav(infile, outfile, &f, WAVE_FLOAT, 0.0);
}
