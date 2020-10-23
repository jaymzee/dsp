#include "wave.h"
#include "circular_filter.h"
#include <stdio.h>
#include <stdlib.h>

unsigned b_indx[2] = {1, 3500};
double   b_val[2]  = {0.4, 0.4};
unsigned a_indx[1] = {3000};
double   a_val[1]  = {0.6};

int main(int argc, char *argv[])
{
    const char *infile, *outfile;
    struct cirfltr *fs;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavreverb infile outfile\n");
        return EXIT_FAILURE;
    }

    infile = argv[1];
    outfile = argv[2];

    fs = cirfltr_create(5000, 2, b_indx, b_val, 2, a_indx, a_val);
    return wave_filter(infile, outfile, (filter_func)cirfltr_sample, fs,
                       WAVE_PCM, 2.0);
}
