#ifndef DSP_FRACTIONAL_DELAY_H_INCLUDED
#define DSP_FRACTIONAL_DELAY_H_INCLUDED

/*
 * circular buffer implementation of a fractional delay line 
 */

struct delay {
    double *w;       /* delay line */
    unsigned N;      /* length of w */
    unsigned offset; /* current start of buffer within w */
};

/* allocate and initialize */
struct delay *delay_create(unsigned N);

/* free state object */
void delay_destroy(struct delay *s);

/* decrement offset within w buffer (advance delay line by one sample) */
void delay_dec(struct delay *s);

/* increment offset within w buffer */
void delay_inc(struct delay *s);

/* return w[n] while handling wrapping */
double delay_w(struct delay *s, double n);

/* return pointer to w[0] */
double *delay_w0(struct delay *s);

#endif /* FRACTIONAL_DELAY_H */
