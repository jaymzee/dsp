#ifndef DSP_CIRCULAR_FILTER_H_INCLUDED
#define DSP_CIRCULAR_FILTER_H_INCLUDED

#include <stddef.h>

/*
 * circular buffer implementation of a canonical filter 
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

/* circular filter state */
struct cirfltr {
    double *w;        /* delay line */
    double *a_val;    /* a coefficient values */
    double *b_val;    /* b coefficient values */
    size_t *a_indx;   /* a coefficient index */
    size_t *b_indx;   /* b coefficient index */
    size_t Na;        /* length of a */
    size_t Nb;        /* length of b */
    size_t N;         /* length of w */
    size_t offset;    /* current start of buffer within w */
};

/* allocate and initialize */
struct cirfltr *
cirfltr_create(size_t N, size_t Nb, size_t *b_indx, double *b_val,
               size_t Na, size_t *a_indx, double *a_val);

/* free state object */
void cirfltr_destroy(struct cirfltr *s);

/* decrement offset within w buffer (advance delay line by one) */
void cirfltr_dec(struct cirfltr *s);

/* increment offset within w buffer */
void cirfltr_inc(struct cirfltr *s);

/* return pointer to w[n] while handling wrapping */
double * cirfltr_w(struct cirfltr *s, size_t n);

/* process one sample through circular filter */
float cirfltr_sample(struct cirfltr *s, float x);

#endif /* CIRCULAR_FILTER_H */
