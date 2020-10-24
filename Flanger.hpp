#include "IFilter.h"
#include "FractionalDelay.h"
#include <cmath>

namespace dsp {

class Flanger: public IFilter {
public:
    const double T;     // sample period
    const int N;        // length of delay line
    FractionalDelay w;  // delay line
    double rate;        // rate of flanger
    double phase;       // current phase of flanger (time)

    Flanger(size_t n, int fs, double rate = 0.0) :
        T(1.0 / fs), N(n), w(n), rate(rate), phase(0.0) {}

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
