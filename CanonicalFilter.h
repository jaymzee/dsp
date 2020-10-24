#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "IFilter.h"
#include <vector>

namespace dsp {

/* canonical filter for signal processing */
class CanonicalFilter: public IFilter {
public:
    CanonicalFilter(size_t n,
                    std::vector<double> b,
                    std::vector<double> a) : w(n), b(b), a(a) {}
    std::vector<double> w;  /* delay line */
    std::vector<double> b;  /* b coefficients - feed forward */
    std::vector<double> a;  /* a coefficients - feedback */

    /* process one sample through filter */
    float ProcessSample(float x);
};

}
#endif
