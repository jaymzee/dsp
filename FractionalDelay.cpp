#include "FractionalDelay.h"

/*
 * FractionalDelay::FractionalDelay() - construct a fractional delay line 
 * length: length of delay line
 */
FractionalDelay::FractionalDelay(unsigned length) : w(length), offset(0)
{
}

/*
 * FractionalDelay::operator--() - advance delay line by one sample
 *
 * Return: reference to *this
 */
FractionalDelay& FractionalDelay::operator--()
{
    if (--offset < 0)
        offset += w.size();
    return *this;
}

/*
 * FractionalDelay::operator--() - retreat delay line by one sample
 *
 * Return: reference to *this
 */
FractionalDelay& FractionalDelay::operator++()
{
    unsigned N = w.size();
    if (++offset > N)
        offset -= N;
    return *this;
}

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
    unsigned N = w.size();
    int first = (int)n;

    w1 = w[(offset + first) % N];
    w2 = w[(offset + first + 1) % N];
    f = n - first;
    return (1.0 - f) * w1 + f * w2;
}

/*
 * FractionalDelay::operator[](int) - reference tap[n]
 * n: index of delay line tap
 *
 * Return: reference to w[n] (offset within and modulo wrap w)
 */
double& FractionalDelay::operator[](int n)
{
    return w[(offset + n) % w.size()];
}

/*
 * FractionalDelay::length() - length of delay line
 */
unsigned FractionalDelay::Length()
{
    return w.size();
}
