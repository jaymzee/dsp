#ifndef DSP_DELAYLINE_H_INCLUDED
#define DSP_DELAYLINE_H_INCLUDED

/*
 * circular buffer implementation of a fractional delay line
 */

struct delay {
    double *w;      /* delay line */
    int N;       /* length of w */
    int offset;  /* current start of buffer within w */
};

/* allocate and initialize */
struct delay *delay_create(int N);

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

#endif
