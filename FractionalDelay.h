#ifndef DSP_FRACTIONALDELAY_H_INCLUDED
#define DSP_FRACTIONALDELAY_H_INCLUDED

#include <vector>

/*
 * circular buffer implementation of a fractional delay line (CPP)
 */

class Delay {
    std::vector<double> w;       /* delay line */
    unsigned offset;             /* current start of buffer within w */
public:
    Delay(unsigned length);
    Delay& operator--();         /* (advance delay line by one sample) */
    Delay& operator++();         /* (retreat delay line by one sample) */
    double operator[](double n); /* interpolate w[n] */
    double& operator[](int n);   /* reference to w[n] */
    unsigned Length();           /* length of delay line */
};

#endif
