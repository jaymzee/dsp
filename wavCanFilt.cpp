extern "C" {
#include "wave.h"
}
#include "CanonicalFilter.h"
#include <cstdio>
#include <cstdlib>

CanonicalFilter f = {
    {0.0, 0.0, 0.0},    //w
    {0.2, 0.2, 0.2},    //b
    {1.0, 0.3, 0.3}     //a
};

int main(int argc, char *argv[])
{
    const char *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavCanFilt infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    int rv = wave_filter(infile, outfile,
                         (filter_func)CanonicalFilter::sample_, &f,
                         WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
