#ifndef CANONICALFILTER_H
#define CANONICALFILTER_H

/* canonical filter for signal processing */

#include "filter.h"
#include <vector>

class CanonicalFilter {
public:
    std::vector<double> w;  /* delay line */
    std::vector<double> b;  /* b coefficients - feed forward */
    std::vector<double> a;  /* a coefficients - feedback */
    float sample(float x);  /* process one sample through filter */

    // filter function callback for wave_filter()
    inline static float sample_(CanonicalFilter *cf, float x) {
        return cf->sample(x);
    }
};

#endif /* CANONICALFILTER_H */
