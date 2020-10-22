#ifndef CIRCULAR_FILTER_H
#define CIRCULAR_FILTER_H

/*
 * circular buffer implementation of a canonical filter 
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

#include "filter.h"

/* circular filter state */
struct cirfltr {
    double *w;          /* delay line */
    double *a_val;      /* a coefficient values */
    double *b_val;      /* b coefficient values */
    unsigned *a_indx;   /* a coefficient index */
    unsigned *b_indx;   /* b coefficient index */
    unsigned Na;        /* length of a */
    unsigned Nb;        /* length of b */
    unsigned N;         /* length of w */
    unsigned offset;    /* current start of buffer within w */
};

/* allocate and initialize */
struct cirfltr *
cirfltr_create(unsigned N, unsigned Nb, unsigned *b_indx, double *b_val,
               unsigned Na, unsigned *a_indx, double *a_val);

/* free state object */
void cirfltr_destroy(struct cirfltr *s);

/* decrement offset within w buffer (advance delay line by one) */
void cirfltr_dec(struct cirfltr *s);

/* increment offset within w buffer */
void cirfltr_inc(struct cirfltr *s);

/* return pointer to w[n] while handling wrapping */
double * cirfltr_w(struct cirfltr *s, unsigned n);

/* process one sample through circular filter */
float cirfltr_sample(struct cirfltr *s, float x);

#endif /* CIRCULAR_FILTER_H */
