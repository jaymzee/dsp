#include "DirectFormFilter.h"
#include <algorithm>

namespace dsp {

using std::vector;

DirectForm1Filter::DirectForm1Filter(vector<double> b, vector<double> a)
: x(b.size()), y(a.size()), b{b}, a{a}
{
}

/* filter one sample using direct form I
 * x: input sample to process
 *
 * Return: output sample
 */
double DirectForm1Filter::ProcessSample(double x0)
{
    double yz = 0.0, yp = 0.0;  // partial sums

    x[0] = x0;
    for (int n = b.size() - 1; n >= 0; n--) {
        yz += b[n] * x[n];
    }
    for (int n = a.size() - 1; n > 0; n--) {
        yp -= a[n] * y[n];
    }
    y[0] = yz + yp;

    for (int n = x.size() - 1; n > 0; n--) {
        x[n] = x[n - 1];
    }
    for (int n = y.size() - 1; n > 0; n--) {
        y[n] = y[n - 1];
    }

    return y[0];
}

DirectForm2Filter::DirectForm2Filter(vector<double> b, vector<double> a)
: w(std::max(b.size(), a.size())), b{b}, a{a}
{
}

/* filter one sample using direct form II
 * x: input sample to process
 *
 * Return: output sample
 */
double DirectForm2Filter::ProcessSample(double x)
{
    double y = 0.0;
    double w0 = x;

    for (int n = a.size() - 1; n > 0; n--) {
        w0 -= a[n] * w[n];
    }
    w[0] = w0;

    for (int n = b.size() - 1; n >= 0; n--) {
        y += b[n] * w[n];
    }

    for (int n = w.size() - 1; n > 0; n--) {
        w[n] = w[n - 1];
    }

    return y;
}

DirectForm2TFilter::DirectForm2TFilter(vector<double> b, vector<double> a)
: v(std::max(b.size(), a.size())), b{b}, a{a}
{
    // make a and b the same size for simplicity
    if (b.size() > a.size()) {
        a.resize(b.size(), 0.0);
    } else if (a.size() > b.size()) {
        b.resize(a.size(), 0.0);
    }
}

/* filter one sample using transposed direct form II
 * x: input sample to process
 *
 * Return: output sample
 */
double DirectForm2TFilter::ProcessSample(double x)
{
    const int M = v.size() - 1;

    v[0] = b[0] * x + v[1];

    for (int i = 1; i < M; i++) {
        v[i] = b[i] * x - a[i] * v[0] + v[i+1];
    }
    v[M] = b[M] * x - a[M] * v[0];

    return v[0];
}

} // namespace dsp
