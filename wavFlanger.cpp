#include "FlangerFilter.h"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavFlanger infile outfile\n");
        return EXIT_FAILURE;
    }

    dsp::Flanger f(200, 0.125);

    return dsp::WaveFilter(argv[1], argv[2], &f, WAVE_PCM, 0.0);
}
