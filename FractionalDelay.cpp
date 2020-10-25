#include "FractionalDelay.h"

namespace dsp {
/*
 * FractionalDelay::operator[](double) - interpolate tap[n]
 * n: index of delay line tap, must be >= 0 but may have a fractional part
 *    since there is a fractional part to n, linearly interpolate the samples
 *
 * Return: tap[n] (offset within and modulo wrap w)
 */
double FractionalDelay::operator[](double n)
{
    double w1, w2, f;
    int first = (int)n;

    w1 = w[(offset + first) % N];
    w2 = w[(offset + first + 1) % N];
    f = n - first;
    return (1.0 - f) * w1 + f * w2;
}

}
