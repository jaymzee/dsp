#include "BiQuadFilter.h"

namespace dsp {

// construct BiQuadFilter
// b: quadratic polynomial for zeros
// a: quadratic polynomial for poles
BiQuadFilter::BiQuadFilter(
    std::array<double,3>b,
    std::array<double,3>a
): x{}, y{}, b(b), a(a)
{
}

// filter one sample using direct form I
// x: input sample to process
// Return: output sample
double BiQuadFilter::ProcessSample(double x0)
{
    double yz = b[0] * x0 + b[1] * x[1] + b[2] * x[2];
    double yp = -a[1] * y[1] - a[2] * y[2];
    x[0] = x0;
    y[0] = yz + yp;

    x[2] = x[1];
    x[1] = x[0];
    y[2] = y[1];
    y[1] = y[0];

    return y[0];
}

} // namespace dsp
