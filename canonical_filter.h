#ifndef CANONICAL_FILTER_H
#define CANONICAL_FILTER_H

/* canonical filter for signal processing */

#include "filter.h"

/* canonical filter state */
struct canfltr {
    double *w;      /* delay line */
    double *a;      /* a coefficients - feedback */
    double *b;      /* b coefficients - feed forward */
    unsigned N;     /* length of w, a, b */
};

/* allocate and initialize state object */
struct canfltr *
canfltr_create(unsigned N, double *b, double *a);

/* free state object */
void canfltr_destroy(struct canfltr *s);

/* process one sample through canonical filter */
float canfltr_sample(struct canfltr *state, float x);

#endif /* CANONICAL_FILTER_H */