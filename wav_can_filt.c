#include "wave.h"
#include "canonical_filter.h"
#include <stdio.h>
#include <stdlib.h>

double b[3] = {0.2, 0.2, 0.2};
double a[3] = {1.0, 0.3, 0.3};

int main(int argc, char *argv[])
{
    struct canfilt_state *fs;
    int rv;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavcanfilt infile outfile\n");
        return EXIT_FAILURE;
    }

    fs = canfilt_create(3, b, a);
    rv = wave_filter(argv[1], argv[2], canfilt_procsamp, fs, WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
