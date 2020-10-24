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
    size_t offset_;                 /* current start of buffer within w */
public:
    const size_t N;                 /* length of delay line */
    std::map<size_t, double> b;     /* feedforward coefficients */
    std::map<size_t, double> a;     /* feedback coefficients */
    // construct size n delay line
    CircularFilter(size_t n) : w_(n), offset_(0), N(n) {}
    // advance delay line by one sample
    void Shift() { if (--offset_ < 0) offset_ += N; }
    // retreat delay line by one sample
    void Unshift() { if (++offset_ > N) offset_ -= N; }
    // return reference to w[n] (offset and modulo wrap w[n])
    double& operator[](size_t n) { return w_[(offset_ + n) % N]; }
    // return reference to w[n] (offset and modulo wrap w[n])
    double& w(size_t n) { return w_[(offset_ + n) % N]; }
    /* process one sample through filter */
    float ProcessSample(float x);
};

} // namespace dsp

#endif
