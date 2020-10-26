#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "Filter.hpp"
#include <vector>

namespace dsp {

/* canonical filter for signal processing */
class CanonicalFilter: public Filter {
    std::vector<double> w;  /* delay line */
public:
    CanonicalFilter(std::vector<double> b, std::vector<double> a);
    std::vector<double> b;  /* b coefficients - feed forward */
    std::vector<double> a;  /* a coefficients - feedback */

    /* process one sample through filter */
    float ProcessSample(float x);
};

}
#endif
