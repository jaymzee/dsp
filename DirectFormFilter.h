#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "Filter.hpp"
#include <vector>

/* direct form filters
 * a[0] should always be 1.0
 * an FIR only filter can be defined using the b vector and a = {1.0}
 * an IIR only filter can be defined using the a vector and b = {1.0}
 */

namespace dsp {

/* DirectForm1Filter
 *
 * start with the Z transform of a filter with transfer function H(z):
 *
 *  Y(z) = H(z)·X(z)
 *  Y(z) = N(z)/D(z)·X(z)
 *  D(z)·Y(z) = N(z)·X(z)
 *
 * inverse Z transform and collecting terms to one side gives:
 *
 *  y[n] =   b[0]x[n]   + b[1]x[n-1] + ... + b[L]x[n-L]
 *         - a[1]y[n-1] - a[2]y[n-2] - ... - a[M]y[n-M]
 *
 *              b0
 * x[n] ----┬---|>-→(+)-------┬---→ y[n]
 *          ↓        ↑        ↓
 *         [z]  b1   |  -a1  [z]
 *          ├---|>-→(+)←-<|---┤
 *          ↓        ↑        ↓
 *         [z]  b2   |  -a2  [z]
 *          └---|>-→(+)←-<|---┘
 *
 */
class DirectForm1Filter: public Filter {
    std::vector<double> x;  // delay line for input
    std::vector<double> y;  // delay line for output
public:
    std::vector<double> b;  // b coefficients - feed forward
    std::vector<double> a;  // a coefficients - feedback

    DirectForm1Filter(std::vector<double> b, std::vector<double> a);
    float ProcessSample(float x); // process one sample through filter
};

/* DirectfForm2Filter
 *
 * Starting with the direct form I equation above:
 *
 * y[n] =   b[0]x[n]   + b[1]x[n-1] + ... + b[L]x[n-L]
 *        - a[1]y[n-1] - a[2]y[n-2] - ... - a[M]y[n-M]
 *
 * You can split the poles and zeros into separate blocks. Since the system
 * is linear, you can swap these blocks. Now the delays will have the exact
 * same values, so they can be combined.
 *
 * y[n] =   b[0]w[n]   + b[1]w[n-1] + ... + b[L]w[n-L]
 *        - a[1]w[n-1] - a[2]w[n-2] - ... - a[L]w[n-L]
 *
 *                w[n]   b0
 * x[n] --→(+)-------┬---|>--(+)--→ y[n]
 *          ↑        ↓        ↑
 *          |  -a1  [z]  b1   |
 *         (+)←-<|---┼---|>-→(+)
 *          ↑        ↓        ↑
 *          |  -a2  [z]  b2   |
 *          └---<|---┴---|>---┘
 *
 */
class DirectForm2Filter: public Filter {
    std::vector<double> w;  // delay line
public:
    std::vector<double> b;  // b coefficients - feed forward
    std::vector<double> a;  // a coefficients - feedback

    DirectForm2Filter(std::vector<double> b, std::vector<double> a);
    float ProcessSample(float x); // process one sample through filter
};

/* DirectForm1TFilter - transposed direct form I
 *
 * Starting with the direct form I signal flow:
 *
 * change all adders to nodes
 * change all nodes to adders
 * reverse the direction of all signal flow
 * swap inputs and outputs
 *
 *               v[n]   b0
 * x[n] --→(+)-------┬--|>--→(+)--→ y[n]
 *          ↑        |        ↑
 *         [z]       |       [z]
 *          ↑   -a1  |  b1    ↑
 *         (+)←--<|--┼--|>--→(+)
 *          ↑        |        ↑
 *         [z]       |       [z]
 *          ↑   -a2  |  b2    ↑
 *          └----<|--┴--|>----┘
 *
 */

/* DirectfForm2TFilter - transposed direct form II
 *
 * Starting with the direct form II signal flow:
 *
 * change all adders to nodes
 * change all nodes to adders
 * reverse the direction of all signal flow
 * swap inputs and outputs
 *
 *             b0      v0[n]
 * x[n] ----┬--|>--→(+)-------┬---→ y[n]
 *          |        ↑ v1[n]  |
 *          |       [z]       |
 *          |  b1    ↑   -a1  |
 *          ├--|>--→(+)←--<|--┤
 *          |        ↑ v2[n]  |
 *          |       [z]       |
 *          |  b1    ↑   -a2  |
 *          └--|>--→(+)←--<|--┘
 *
 */
class DirectForm2TFilter: public Filter {
    std::vector<double> v;  // delay line
public:
    std::vector<double> b;  // b coefficients - zeros
    std::vector<double> a;  // a coefficients - poles

    DirectForm2TFilter(std::vector<double> b, std::vector<double> a);
    float ProcessSample(float x); // process one sample through filter
};

}

#endif
