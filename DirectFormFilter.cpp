#include "DirectFormFilter.h"
#include <algorithm>

namespace dsp {

DirectForm1Filter::DirectForm1Filter(std::vector<double>b,
                                     std::vector<double>a) :
    x(b.size()), y(a.size()), b(b), a(a)
{
}

/* filter one sample using direct form I
 * x: input sample to process
 *
 * Return: output sample
 */
float DirectForm1Filter::ProcessSample(float x0)
{
    double yz = 0.0, yp = 0.0;

    x[0] = x0;
    for (int n = b.size() - 1; n >= 0; n--)
        yz += b[n] * x[n];
    for (int n = a.size() - 1; n > 0; n--)
        yp -= a[n] * y[n];

    for (int n = x.size() - 1; n > 0; n--)
        x[n] = x[n - 1];
    for (int n = y.size() - 1; n > 0; n--)
        y[n] = y[n - 1];

    return yz + yp;
}

DirectForm2Filter::DirectForm2Filter(std::vector<double>b,
                                       std::vector<double>a) :
    w(std::max(b.size(), a.size())), b(b), a(a)
{
}

/* filter one sample using direct form II
 * x: input sample to process
 *
 * Return: output sample
 */
float DirectForm2Filter::ProcessSample(float x)
{
    double y = 0.0;
    double w0 = x;

    for (int n = a.size() - 1; n > 0; n--)
        w0 -= a[n] * w[n];
    w[0] = w0;

    for (int n = b.size() - 1; n >= 0; n--)
        y += b[n] * w[n];

    for (int n = w.size() - 1; n > 0; n--)
        w[n] = w[n - 1];

    return y;
}

DirectForm2TFilter::DirectForm2TFilter(std::vector<double>b,
                                      std::vector<double>a) :
    v(std::max(b.size(), a.size())), b(b), a(a)
{
}

/* filter one sample using transposed direct form II
 * x: input sample to process
 *
 * Return: output sample
 */
float DirectForm2TFilter::ProcessSample(float x)
{
    const int a_sz = a.size();
    const int b_sz = b.size();
    double y = v[0] + b[0] * x;

    // update zeros
    v[v.size()-1] = 0.0;
    for (int n = 1; n < b_sz; n++)
        v[n-1] = b[n] * x + v[n];

    // update poles
    for (int n = 1; n < a_sz; n++)
        v[n-1] -= a[n] * y;

    return y;
}

} // namespace dsp
