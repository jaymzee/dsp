#include "FlangerFilter.h"
#include <cmath>

#define PI 3.14159265358979323846
#define FS 44100

namespace dsp {

// process one sample
float Flanger::ProcessSample(float x) {
    const int N = w.Length();
    double n, y;

    w[0] = x;
    n = (N - 1) * (0.5 * cos(2 * PI * rate * phase) + 0.5);
    y = 0.5 * w[N / 2] + 0.5 * w[n];
    phase += 1.0 / FS;
    --w;

    return y;
}

}
