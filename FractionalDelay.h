#ifndef DSP_FRACTIONALDELAY_H_INCLUDED
#define DSP_FRACTIONALDELAY_H_INCLUDED

#include <vector>

namespace dsp {
/*
 * circular buffer implementation of a fractional delay line (CPP)
 */

class FractionalDelay {
    std::vector<double> w_;         /* delay line */
    size_t offset_;                 /* current start of buffer within w */
public:
    const size_t N;
    FractionalDelay(size_t n) : w_(n), offset_(0), N(n) {}
    /* (advance delay line by one sample) */
    void Shift() { if (--offset_ < 0) offset_ += N; }
    /* (retreat delay line by one sample) */
    void Unshift() { if (++offset_ > N) offset_ -= N; }
    double operator[](double n);    /* interpolate w[n] */
    /* reference to w[n] */
    double& operator[](int n) { return w_[(offset_ + n) % N]; }
};

}

#endif
