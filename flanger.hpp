#include "filter.hpp"
#include "delay.h"
#include <cmath>

namespace dsp {

class Flanger: public Filter {
    Delay w;            // delay line
    int N;              // length of delay line
    double T;           // sample period
public:
    double rate;        // rate of flanger
    double phase;       // current phase of flanger (time)

    Flanger(int n, int fs, double rate = 0.0)
    : w(n), N{n}, T{1.0 / fs}, rate{rate}, phase{} {}

    // process one sample
    double ProcessSample(double x) {
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
