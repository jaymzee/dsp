#include "wave.h"
#include "cirfltr.h"
#include <stdio.h>
#include <stdlib.h>

int     b_i[2] = {1, 3500};
double  b_v[2] = {0.4, 0.4};
int     a_i[1] = {3000};
double  a_v[1] = {0.6};

int main(int argc, char *argv[])
{
    const char *infile, *outfile;
    struct cirfltr *cf;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavreverb infile outfile\n");
        return EXIT_FAILURE;
    }

    infile = argv[1];
    outfile = argv[2];

    cf = cirfltr_create(5000, 2, b_i, b_v, 2, a_i, a_v);
    return wave_filter(infile, outfile, (filter_func)cirfltr_sample, cf,
                       WAVE_PCM, 2.0);
}
