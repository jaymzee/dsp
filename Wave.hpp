#ifndef DSP_WAVE_HPP_INCLUDED
#define DSP_WAVE_HPP_INCLUDED

extern "C" {
#include "wave.h"
}
#include "IFilter.h"

namespace dsp {

/* callback for wave_filter()
 */
float WaveFilterCallback(IFilter *f, float x) {
    return f->ProcessSample(x);
}

/* WaveFilter() C++ wrapper for wave_filter()
 * infile: filename of input wav file
 * outfile: filename of output wav file
 * format: output wav file format type
 * duration: length of time to use input wav file as the source
 */
int WaveFilter(const char *infile, const char *outfile,
               IFilter* f, int format, double duration) {
    return wave_filter(infile, outfile,
                       (filter_func)WaveFilterCallback, f,
                       format, duration);
}

} // namespace dsp

#endif
