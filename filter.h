#ifndef DSP_FILTER_H_INCLUDED
#define DSP_FILTER_H_INCLUDED

/* 
 * function pointer for all sample by sample processing algorithms
 * x: input sample to process
 * state: pointer to the state of the filter
 *
 * Return: output sample
 */
typedef double (*filter_func)(void *state, double x);

#endif /* FILTER_H */
