#include "CircularFilter.h"
/*
 * CircularFilter::CircularFilter() - construct a CircularFilter
 * length: length of delay line
 */
CircularFilter::CircularFilter(unsigned length) : w_(length), offset_(0)
{
}

/*
 * CircularFilter::operator-- advance delay line by one sample
 *
 */
CircularFilter& CircularFilter::operator--()
{
    if (--offset_ < 0)
        offset_ += w_.size();
    return *this;
}

/*
 * CircularFilter::Shift() advance delay line by one sample
 *
 */
void CircularFilter::Shift()
{
    if (--offset_ < 0)
        offset_ += w_.size();
}

/*
 * CircularFilter::operator++ retreat delay line by one sample
 *
 */
CircularFilter& CircularFilter::operator++()
{
    unsigned N = w_.size();
    if (++offset_ > N)
        offset_ -= N;
    return *this;
}

/*
 * CircularFilter::Unshift() retreat delay line by one sample
 *
 */
void CircularFilter::Unshift()
{
    unsigned N = w_.size();
    if (++offset_ > N)
        offset_ -= N;
}

/*
 * CircularFilter::operator[] return ref to w[n] (offset and modulo wrap w[n])
 */
double& CircularFilter::operator[](unsigned n)
{
    return w_[(offset_ + n) % w_.size()];
}

/*
 * CircularFilter::w() return reference to w[n] (offset and modulo wrap w[n])
 */
double& CircularFilter::w(unsigned n)
{
    return w_[(offset_ + n) % w_.size()];
}

/*
 * CircularFilter::Length() return length of delay line
 */
unsigned CircularFilter::Length()
{
    return w_.size();
}

/*
 * CircularFilter::Sample() process one sample
 * x: input sample
 *
 * Return: output sample
 */
float CircularFilter::ProcessSample(float x)
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
