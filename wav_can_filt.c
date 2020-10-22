#include "wave.h"
#include "canonical_filter.h"
#include <stdio.h>
#include <stdlib.h>

double b[3] = {0.2, 0.2, 0.2};
double a[3] = {1.0, 0.3, 0.3};

int main(int argc, char *argv[])
{
    struct canfltr *fs;
    int rv;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavcanfilt infile outfile\n");
        return EXIT_FAILURE;
    }

    fs = canfltr_create(3, b, a);
    rv = wave_filter(argv[1], argv[2],
                     (filter_func)canfltr_sample,
                     fs, WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
