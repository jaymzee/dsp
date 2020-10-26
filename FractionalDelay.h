#ifndef DSP_FRACTIONALDELAY_H_INCLUDED
#define DSP_FRACTIONALDELAY_H_INCLUDED

#include <vector>

namespace dsp {
/*
 * circular buffer implementation of a fractional delay line
 */

class FractionalDelay {
    std::vector<double> w;  /* delay line */
    int offset;             /* current start of buffer within w */
    int N;
public:
    FractionalDelay(int n);
    /* (advance delay line by one sample) */
    void Shift() { if (--offset < 0) offset += N; }
    /* (retreat delay line by one sample) */
    void Unshift() { if (++offset > N) offset -= N; }
    /* interpolate w[n] */
    double operator[](double n);
    /* reference to w[n] */
    double& operator[](int n) { return w[(offset + n) % N]; }
};

}

#endif
