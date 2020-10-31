#ifndef DSP_BIQUADFILTER_H_INCLUDED
#define DSP_BIQUADFILTER_H_INCLUDED

#include "Filter.hpp"
#include <array>

/************************************************************************
* biquad filter is a direct form 1 filter where a and b are quadratic   *
* a[0] is assumed to be 1.0                                             *
*                                                                       *
* start with the Z transform of a filter with transfer function H(z):   *
*                                                                       *
*  Y(z) = H(z)·X(z)                                                     *
*  Y(z) = N(z)/D(z)·X(z)                                                *
*  D(z)·Y(z) = N(z)·X(z)                                                *
*                                                                       *
* inverse Z transform and collecting terms to one side gives:           *
*                                                                       *
*  y[n] =   b[0]x[n]   + b[1]x[n-1] + ... + b[L]x[n-L]                  *
*         - a[1]y[n-1] - a[2]y[n-2] - ... - a[M]y[n-M]                  *
*                                                                       *
*              b0                                                       *
* x[n] ----┬---|>-→(+)-------┬---→ y[n]                                 *
*          ↓        ↑        ↓                                          *
*         [z]  b1   |  -a1  [z]                                         *
*          ├---|>-→(+)←-<|---┤                                          *
*          ↓        ↑        ↓                                          *
*         [z]  b2   |  -a2  [z]                                         *
*          └---|>-→(+)←-<|---┘                                          *
*                                                                       *
*************************************************************************/

namespace dsp {

class BiQuadFilter: public Filter {
    std::array<double,3> x;  // delay line for input
    std::array<double,3> y;  // delay line for output
public:
    std::array<double,3> b;  // b coefficients - feed forward
    std::array<double,3> a;  // a coefficients - feedback

    BiQuadFilter(std::array<double,3> b, std::array<double,3> a);
    double ProcessSample(double x); // process one sample through filter
};

}

#endif
