extern "C" {
#include "wave.h"
}
#include "FractionalDelay.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979323846
#define FS 44100

struct Flanger
{
    double rate;    //rate of flanger
    double phase;   //current phase of flanger (time)
    Delay tap;      //delay line
    //process one sample
    static float sample(void *state, float x);
};

float Flanger::sample(void *state, float x)
{
    Flanger &fl = *(Flanger *)state;
    const int N = fl.tap.length();

    fl.tap[0] = x;
    const double n = (N - 1) * (0.5 * cos(2 * PI * fl.rate * fl.phase) + 0.5);
    const double y = 0.5 * fl.tap[N / 2] + 0.5 * fl.tap[n];
    --fl.tap;
    fl.phase += 1.0 / FS;

    return y;
}

int main(int argc, char *argv[])
{
    const char *infile, *outfile;

    if (argc != 3) {
        fprintf(stderr, "Usage: wavFlanger infile outfile\n");
        return EXIT_FAILURE;
    }
    infile = argv[1];
    outfile = argv[2];

    Flanger f = {0.125, 0.0, Delay(200)};
    int rv = wave_filter(infile, outfile, (filter_func)Flanger::sample, &f,
                         WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
