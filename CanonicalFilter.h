#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "Filter.hpp"
#include <vector>

namespace dsp {

/* canonical filter for signal processing
 * a[0] should always be 1.0
 * an FIR only filter can be defined using the b vector and a = {1.0}
 * an IIR only filter can be defined using the a vector and b = {1.0}
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
