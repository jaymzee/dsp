#include "circular.h"

namespace dsp {

Circular::Circular(int n)
: w_(n), offset{}, N{n}
{
}

/*
 * Circular::ProcessSample() process one sample
 * x: input sample
 *
 * Return: output sample
 */
double Circular::ProcessSample(double x)
{
    double y, w0;

    // c is a coefficient from sparse arrays a and b
    //  .first is the coefficient index
    //  .second is the actual coefficient

    // feedback terms
    w0 = x;
    for (auto c : a)
        w0 -= c.second * w(c.first);
    w(0) = w0;

    // feed forward terms
    y = 0.0;
    for (auto c : b)
        y += c.second * w(c.first);

    Shift();
    return y;
}

}
