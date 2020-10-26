#ifndef DSP_WAVE_HPP_INCLUDED
#define DSP_WAVE_HPP_INCLUDED

extern "C" {
#include "wave.h"
}
#include "Filter.hpp"

namespace dsp {

/* callback for wave_filter()
 */
inline float WaveFilterProcessSample(Filter *f, float x) {
    return f->ProcessSample(x);
}

/* WaveFilter() C++ wrapper for wave_filter()
 * infile: filename of input wav file
 * outfile: filename of output wav file
 * format: output wav file format type
 * duration: length of time to use input wav file as the source
 */
inline int WaveFilter(const char *infile, const char *outfile,
                      Filter* f, int format, double duration) {
    return wave_filter(infile, outfile,
                       (filter_func)WaveFilterProcessSample, f,
                       format, duration);
}

} // namespace dsp

#endif
