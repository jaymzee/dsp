#ifndef DSP_CIRCULARFILTER_H_INCLUDED
#define DSP_CIRCULARFILTER_H_INCLUDED

#include "IFilter.h"
#include <vector>
#include <map>

namespace dsp {

/*
 * circular buffer implementation of a canonical filter (CPP)
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse, thus filtering is very efficient when
 * there are a small number of non-zero coefficients for a and b
 */
class CircularFilter: public dsp::IFilter {
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
    float ProcessSample(float x);   /* process one sample through filter */
};

}

#endif
