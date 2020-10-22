#ifndef FRACTIONAL_DELAY_H
#define FRACTIONAL_DELAY_H

/*
 * circular buffer implementation of a fractional delay line 
 */

struct delay_state {
    double *w;       /* delay line */
    unsigned N;      /* length of w */
    unsigned offset; /* current start of buffer within w */
};

/* allocate and initialize */
struct delay_state *delay_create(unsigned N);

/* free state object */
void delay_destroy(struct delay_state *s);

/* decrement offset within w buffer (advance delay line by one sample) */
void delay_dec(struct delay_state *s);

/* increment offset within w buffer */
void delay_inc(struct delay_state *s);

/* return w[n] while handling wrapping */
double delay_w(struct delay_state *s, double n);

/* return pointer to w[0] */
double *delay_w0(struct delay_state *s);

#endif /* FRACTIONAL_DELAY_H */
