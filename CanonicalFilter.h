#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "IFilter.h"
#include <vector>
#include <algorithm>

namespace dsp {

/* canonical filter for signal processing */
class CanonicalFilter: public IFilter {
    std::vector<double> w;  /* delay line */
public:
    CanonicalFilter(std::vector<double> b,
                    std::vector<double> a) :
                    w(std::max(a.size(), b.size())), b(b), a(a) {}
    std::vector<double> b;  /* b coefficients - feed forward */
    std::vector<double> a;  /* a coefficients - feedback */

    /* process one sample through filter */
    float ProcessSample(float x);
};

}
#endif
