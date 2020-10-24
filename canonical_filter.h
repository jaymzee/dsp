#ifndef DSP_CANONICAL_FILTER_H_INCLUDED
#define DSP_CANONICAL_FILTER_H_INCLUDED

/* canonical filter for signal processing */

#include <stddef.h>

/* canonical filter state */
struct canfltr {
    double *w;      /* delay line */
    double *a;      /* a coefficients - feedback */
    double *b;      /* b coefficients - feed forward */
    size_t N;       /* length of w, a, b */
};

/* allocate and initialize state object */
struct canfltr *
canfltr_create(size_t N, double *b, double *a);

/* free state object */
void canfltr_destroy(struct canfltr *s);

/* process one sample through canonical filter */
float canfltr_sample(struct canfltr *state, float x);

#endif
