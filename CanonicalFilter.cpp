#include "CanonicalFilter.h"

/*
 * CanonicalFilter::sample() - process one sample through canonical filter
 * x: input sample to process
 *
 * Return: output sample
 */
float CanonicalFilter::ProcessSample(float x)
{
    double y, w0;

    w0 = x;
    for (int n = a.size() - 1; n > 0; n--)
        w0 -= a[n] * w[n];
    w[0] = w0;

    y = 0.0;
    for (int n = b.size() - 1; n >= 0; n--)
        y += b[n] * w[n];

    for (int n = w.size() - 1; n > 0; n--)
        w[n] = w[n - 1];

    return y;
}

