#ifndef DSP_FRACTIONAL_DELAY_H_INCLUDED
#define DSP_FRACTIONAL_DELAY_H_INCLUDED

/*
 * circular buffer implementation of a fractional delay line 
 */

struct fracdelay {
    double *w;      /* delay line */
    int N;       /* length of w */
    int offset;  /* current start of buffer within w */
};

/* allocate and initialize */
struct fracdelay *fracdelay_create(int N);

/* free state object */
void fracdelay_destroy(struct fracdelay *s);

/* decrement offset within w buffer (advance delay line by one sample) */
void fracdelay_dec(struct fracdelay *s);

/* increment offset within w buffer */
void fracdelay_inc(struct fracdelay *s);

/* return w[n] while handling wrapping */
double fracdelay_w(struct fracdelay *s, double n);

/* return pointer to w[0] */
double *fracdelay_w0(struct fracdelay *s);

#endif /* FRACTIONAL_DELAY_H */
