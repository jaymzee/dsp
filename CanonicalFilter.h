#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "Filter.hpp"
#include <vector>

namespace dsp {

/* canonical filter (direct form II) for signal processing
 * a[0] should always be 1.0
 * an FIR only filter can be defined using the b vector and a = {1.0}
 * an IIR only filter can be defined using the a vector and b = {1.0}
 *
 * Y(Z) = H(Z)·X(Z)
 * Y(Z) = N(Z)/D(Z)·X(Z)
 * y[n] =   b[0]x[n]   + b[1]x[n-1] + ... + b[L]x[n-L]    (direct form I)
 *        - a[1]y[n-1] - a[2]y[n-2] - ... - a[M]y[n-M]
 *
 * y[n] =   b[0]w[n]   + b[1]w[n-1] + ... + b[L]w[n-L]    (direct form II)
 *        - a[1]w[n-1] - a[2]w[n-2] - ... - a[L]w[n-L]
 *
 *                  w0   b0
 * x[n] --→(+)-------┬--|>---(+)--→ y[n]
 *          ↑        ↓        ↑
 *          |       [z]  b1   |
 *         (+)←--<|--┼--|>--→(+)
 *          ↑  -a1   ↓        ↑
 *          |       [z]  b2   |
 *          └----<|--┴--|>----┘
 *             -a2  w2
 */
class CanonicalFilter: public Filter {
    std::vector<double> w;  // delay line
public:
    std::vector<double> b;  // b coefficients - feed forward
    std::vector<double> a;  // a coefficients - feedback

    CanonicalFilter(std::vector<double> b, std::vector<double> a);
    float ProcessSample(float x); // process one sample through filter
};

}

#endif
