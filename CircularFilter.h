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
    std::vector<double> w_;         /* delay line buffer */
    unsigned offset_;               /* current start of buffer within w */
public:
    std::map<unsigned, double> b;   /* feedforward coefficients */
    std::map<unsigned, double> a;   /* feedback coefficients */
    CircularFilter(unsigned length);
    CircularFilter& operator--();   /* advance delay line by one sample */
    void Shift();                   /* advance delay line by one sample */
    CircularFilter& operator++();   /* retreat delay line by one sample */
    void Unshift();                 /* retreat delay line by one sample */
    double& operator[](unsigned n); /* reference to w[n modulo] */
    double& w(unsigned n);          /* reference to w[n modulo] */
    unsigned Length();              /* length of delay line */
    float Sample(float x);          /* process one sample through filter */

    /* filter_func callback for wave_filter() */
    inline static float sample(CircularFilter *cf, float x) {
        return cf->Sample(x);
    }
};

#endif /* CIRCULARFILTER_H */
