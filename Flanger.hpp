#include "IFilter.h"
#include "FractionalDelay.h"
#include <cmath>

namespace dsp {

class Flanger: public IFilter {
    FractionalDelay w;  // delay line
    int N;              // length of delay line
public:
    double T;           // sample period
    double rate;        // rate of flanger
    double phase;       // current phase of flanger (time)

    Flanger(int n, int fs, double rate = 0.0) :
        w(n), N(n), T(1.0 / fs), rate(rate), phase(0.0) {}

    // process one sample
    float ProcessSample(float x) {
        double n, y;

        w[0] = x;
        n = (N - 1) * (0.5 * cos(2 * pi * rate * phase) + 0.5);
        y = 0.5 * w[N / 2] + 0.5 * w[n];
        phase += T;
        w.Shift();

        return y;
    }
};

}
