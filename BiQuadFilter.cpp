#include "BiQuadFilter.h"

namespace dsp {

// construct BiQuadFilter
// b: quadratic polynomial for zeros
// a: quadratic polynomial for poles
BiQuadFilter::BiQuadFilter(
    std::array<double,3>b,
    std::array<double,3>a
): x1{}, x2{}, y1{}, y2{}, b(b), a(a)
{
}

// filter one sample using direct form I
// x: input sample to process
// Return: output sample
double BiQuadFilter::ProcessSample(double x0)
{
    double yz = b[0] * x0 + b[1] * x1 + b[2] * x2;
    double yp = -a[1] * y1 - a[2] * y2;
    double y0 = yz + yp;

    x2 = x1;
    x1 = x0;
    y2 = y1;
    y1 = y0;

    return y0;
}

} // namespace dsp
