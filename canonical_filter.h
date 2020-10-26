#ifndef DSP_CANONICAL_FILTER_H_INCLUDED
#define DSP_CANONICAL_FILTER_H_INCLUDED

/* canonical filter (direct form II) for signal processing
 * a[0] should always be 1.0
 * an FIR only filter can be defined using b vector and a = {1.0}
 * an IIR only filter can be defined using a vector and b = {1.0}
 *
 * Y(Z) = H(Z)·X(Z)
 * Y(Z) = N(Z)/D(Z)·X(Z)
 * y[n] =   b[0]x[n]   + b[1]x[n-1] + ... + b[L]x[n-L]
 *        - a[1]y[n-1] - a[2]y[n-2] - ... - a[M]y[n-M]
 *
 *                  w0   b0
 * x[n] -->(+)----------|>---(+)--> y[n]
 *          ^        v        ^
 *          |       [z]  b1   |
 *         (+)<--<|--|--|>-->(+)
 *          ^  -a1   v        ^
 *          |       [z]  b2   |
 *           ----<|--|--|>----
 *             -a2  w2
 */

/* canonical filter state */
struct canfltr {
    double *w;      /* delay line */
    double *a;      /* a coefficients - feedback */
    double *b;      /* b coefficients - feed forward */
    int N;          /* length of w, a, b */
};

/* allocate and initialize state object */
struct canfltr *
canfltr_create(int N, double *b, double *a);

/* free state object */
void canfltr_destroy(struct canfltr *s);

/* process one sample through canonical filter */
float canfltr_sample(struct canfltr *state, float x);

#endif
