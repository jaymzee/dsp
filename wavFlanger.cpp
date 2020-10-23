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
    float Sample(float x);  // process one sample

    // filter_func callback function for wave_filter()
    inline static float sample(Flanger *f, float x) {
        return f->Sample(x);
    }
};

float Flanger::Sample(float x)
{
    const int N = tap.Length();
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
    if (argc != 3) {
        fprintf(stderr, "Usage: wavFlanger infile outfile\n");
        return EXIT_FAILURE;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];
    Flanger f = {0.125, 0.0, Delay(200)};

    return wave_filter(infile, outfile, (filter_func)Flanger::sample, &f,
                       WAVE_PCM, 0.0);
}
