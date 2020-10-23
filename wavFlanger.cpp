#include "IFilter.h"
#include "FractionalDelay.h"
#include "Wave.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265358979323846
#define FS 44100

class Flanger: public IFilter {
public:
    FractionalDelay w;  // delay line
    double rate;        // rate of flanger
    double phase;       // current phase of flanger (time)

    Flanger(unsigned len, double rate) : w(len), rate(rate), phase(0.0) {}

    // process one sample
    float ProcessSample(float x) {
        const int N = w.Length();
        double n, y;

        w[0] = x;
        n = (N - 1) * (0.5 * cos(2 * PI * rate * phase) + 0.5);
        y = 0.5 * w[N / 2] + 0.5 * w[n];
        phase += 1.0 / FS;
        --w;

        return y;
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: wavFlanger infile outfile\n");
        return EXIT_FAILURE;
    }
    const char *infile = argv[1];
    const char *outfile = argv[2];
    Flanger f(200, 0.125);

    return WaveFilter(infile, outfile, &f, WAVE_PCM, 0.0);
}
