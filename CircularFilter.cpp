#include "CircularFilter.h"
/*
 * CircularFilter::CircularFilter() - construct a CircularFilter
 * length: length of delay line
 */
CircularFilter::CircularFilter(unsigned length) : w(length), offset(0)
{
}

/*
 * CircularFilter::decrement() - advance delay line by one sample
 *
 */
void CircularFilter::decrement()
{
    if (--offset < 0)
        offset += w.size();
}

/*
 * CircularFilter::increment() - retreat delay line by one sample
 *
 */
void CircularFilter::increment()
{
    unsigned N = w.size();
    if (++offset > N)
        offset -= N;
}

/*
 * CircularFilter::tap() - reference tap[n]
 *
 * Return: reference to tap[n] (offset and modulo wrap of w)
 */
double& CircularFilter::tap(unsigned n)
{
    return w[(offset + n) % w.size()];
}

/*
 * CircularFilter::length() - length of delay line
 */
unsigned CircularFilter::length()
{
    return w.size();
}

/*
 * CircularFilter::procsamp() - process one sample
 * x: input sample
 *
 * Return: output sample
 */
float CircularFilter::sample(float x)
{
    double y, w0;

    // c is a coefficient from sparse arrays a and b
    //  .first is the coefficient index
    //  .second is the actual coefficient

    w0 = x;
    for (auto c : a)
        w0 -= c.second * tap(c.first);
    tap(0) = w0;

    y = 0.0;
    for (auto c : b)
        y += c.second * tap(c.first);

    decrement();
    return y;
}
