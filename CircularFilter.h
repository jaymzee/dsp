#ifndef DSP_CIRCULARFILTER_H_INCLUDED
#define DSP_CIRCULARFILTER_H_INCLUDED

#include "Filter.hpp"
#include <vector>
#include <map>

namespace dsp {

/*
 * circular buffer implementation of a canonical filter (CPP)
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse, thus filtering is very efficient when
 * there are a small number of non-zero coefficients for a and b
 */
class CircularFilter: public Filter {
    std::vector<double> w_;     // delay line buffer
    int offset;                 // current start of buffer within w
    int N;                      // length of delay line
public:
    std::map<int, double> b;    // feedforward coefficients
    std::map<int, double> a;    // feedback coefficients

    // construct size n delay line
    CircularFilter(int n);
    // advance delay line by one sample
    void Shift() { if (--offset < 0) offset += N; }
    // retreat delay line by one sample
    void Unshift() { if (++offset > N) offset -= N; }
    // return reference to w[n] (offset and modulo wrap w[n])
    double& operator[](int n) { return w_[(offset + n) % N]; }
    // return reference to w[n] (offset and modulo wrap w[n])
    double& w(int n) { return w_[(offset + n) % N]; }
    // process one sample through filter
    float ProcessSample(float x);
};

} // namespace dsp

#endif
