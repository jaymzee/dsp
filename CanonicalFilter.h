#ifndef DSP_CANONICALFILTER_H_INCLUDED
#define DSP_CANONICALFILTER_H_INCLUDED

#include "IFilter.h"
#include <vector>

/* canonical filter for signal processing */
class CanonicalFilter: public IFilter {
public:
    CanonicalFilter(unsigned len,
                    std::vector<double> b,
                    std::vector<double> a) : w(len), b(b), a(a) {}
    std::vector<double> w;  /* delay line */
    std::vector<double> b;  /* b coefficients - feed forward */
    std::vector<double> a;  /* a coefficients - feedback */

    /* process one sample through filter */
    float ProcessSample(float x);
};

#endif
