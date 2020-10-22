extern "C" {
#include "wave.h"
}
#include "FractionalDelay.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979323846
#define FS 44100

class Flanger
{
public:
    double rate;            // rate of flanger
    double phase;           // current phase of flanger (time)
    Delay tap;              // delay line
    float sample(float x);  // process one sample

    // filter_func callback function for wave_filter()
    inline static float sample_(Flanger *f, float x) {
        return f->sample(x);
    }
};

float Flanger::sample(float x)
{
    const int N = tap.length();
    double n, y;

    tap[0] = x;
    n = (N - 1) * (0.5 * cos(2 * PI * rate * phase) + 0.5);
    y = 0.5 * tap[N / 2] + 0.5 * tap[n];
    phase += 1.0 / FS;
    --tap;

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
    int rv = wave_filter(infile, outfile,
                         (filter_func)Flanger::sample_, &f,
                         WAVE_PCM, 0.0);

    return rv == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
