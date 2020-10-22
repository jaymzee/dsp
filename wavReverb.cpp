extern "C" {
#include "wave.h"
}
#include "CircularFilter.h"
#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
    const char *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavReverb infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    CircularFilter f(5000);
    f.b[1] = 0.4;
    f.b[3500] = 0.4;
    f.a[3000] = 0.6;

    int rv = wave_filter(infile, outfile,
                         (filter_func)CircularFilter::sample, &f,
                         WAVE_PCM, 2.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
