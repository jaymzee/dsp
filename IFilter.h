#ifndef DSP_IFILTER_H_INCLUDED
#define DSP_IFILTER_H_INCLUDED

namespace dsp {

const double pi = 3.14159265358979323846;

/*
 * sample by sample processing interface
 */
class IFilter {
public:
    virtual float ProcessSample(float x) = 0;
};

}
#endif
