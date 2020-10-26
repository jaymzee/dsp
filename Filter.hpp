#ifndef DSP_FILTER_HPP_INCLUDED
#define DSP_FILTER_HPP_INCLUDED

namespace dsp {

const double pi = 3.14159265358979323846;

/*
 * sample by sample processing interface
 */
class Filter {
public:
    virtual float ProcessSample(float x) = 0;
};

}
#endif
