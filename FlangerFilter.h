#include "IFilter.h"
#include "FractionalDelay.h"

namespace dsp {

class Flanger: public IFilter {
public:
    FractionalDelay w;  // delay line
    double rate;        // rate of flanger
    double phase;       // current phase of flanger (time)

    Flanger(unsigned len, double rate) : w(len), rate(rate), phase(0.0) {}
    float ProcessSample(float x); // process one sample
};

}
