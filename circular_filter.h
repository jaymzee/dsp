#ifndef DSP_CIRCULAR_FILTER_H_INCLUDED
#define DSP_CIRCULAR_FILTER_H_INCLUDED

/*
 * circular buffer implementation of a canonical filter 
 * since w is likely to be a large buffer, the arrays for
 * a and b are sparse thus filtering is very efficient if most
 * the values for a and b are zero.
 */

/* circular filter state */
struct cirfltr {
    double *w;      /* delay line */
    double *a_val;  /* a coefficient values */
    double *b_val;  /* b coefficient values */
    int *a_indx;    /* a coefficient index */
    int *b_indx;    /* b coefficient index */
    int Na;         /* length of a */
    int Nb;         /* length of b */
    int N;          /* length of w */
    int offset;     /* current start of buffer within w */
};

/* allocate and initialize */
struct cirfltr *
cirfltr_create(int N, int Nb, int *b_indx, double *b_val,
               int Na, int *a_indx, double *a_val);

/* free state object */
void cirfltr_destroy(struct cirfltr *s);

/* decrement offset within w buffer (advance delay line by one) */
void cirfltr_dec(struct cirfltr *s);

/* increment offset within w buffer */
void cirfltr_inc(struct cirfltr *s);

/* return pointer to w[n] while handling wrapping */
double * cirfltr_w(struct cirfltr *s, int n);

/* process one sample through circular filter */
double cirfltr_sample(struct cirfltr *s, double x);

#endif /* CIRCULAR_FILTER_H */
