#ifndef DSP_CIRCULARFILTER_H_INCLUDED
#define DSP_CIRCULARFILTER_H_INCLUDED

/* 
 * circular buffer implementation of a canonical filter (CPP)
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

#include "filter.h"
#include <vector>
#include <map>

class CircularFilter {
    std::vector<double> w;          /* delay line buffer */
    unsigned offset;                /* current start of buffer within w */
public:
    std::map<unsigned, double> b;   /* feedforward coefficients */
    std::map<unsigned, double> a;   /* feedback coefficients */
    CircularFilter(unsigned length);
    void decrement();               /* advance delay line by one sample */
    void increment();               /* retreat delay line by one sample */
    double& tap(unsigned n);        /* reference to tap[n] */
    unsigned length();              /* length of delay line */
    float sample(float x);          /* process one sample through filter */

    /* filter_func callback for wave_filter() */
    inline static float sample_(CircularFilter *cf, float x) {
        return cf->sample(x);
    }
};

#endif /* CIRCULARFILTER_H */
