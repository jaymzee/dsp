#include "Flanger.hpp"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavFlanger infile outfile\n");
        return EXIT_FAILURE;
    }

    dsp::Flanger f{200, 44100, 0.125};

    return WaveFilter(argv[1], argv[2], &f, WAVE_PCM, 0.0);
}
