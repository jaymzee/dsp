#include "canfltr.h"
#include <stdlib.h>
#include <string.h>

/*
 * canfltr_create() - allocate and initialize a canonical filter
 * N: length of delay line w (and a and b coeeficient arrays)
 * b: b coefficent array (feed forward)
 * a: a coefficent array (feedback)
 *
 * Return: the initialized state structure for the filter
 */
struct canfltr *
canfltr_create(int N, double *b, double *a)
{
    struct canfltr *s;
    s = malloc(sizeof(struct canfltr));
    s->N = N;
    s->w = calloc(N, sizeof(double));
    s->a = calloc(N, sizeof(double));
    s->b = calloc(N, sizeof(double));
    memcpy(s->a, a, N * sizeof(double));
    memcpy(s->b, b, N * sizeof(double));
    s->a[0] = 1.0;
    return s;
}

/*
 * canfltr_destroy() - free memory allocated for canonical filter
 * s: pointer to filter state
 */
void canfltr_destroy(struct canfltr *s)
{
    free(s->b);
    free(s->a);
    free(s->w);
    free(s);
}

/*
 * canfltr_sample() - process one sample through canonical filter
 * x: input sample to process
 * state: pointer to the state of the filter
 *
 * Return: output sample
 */
double canfltr_sample(struct canfltr *state, double x)
{
    int n, N = state->N;
    double *w = state->w;
    double *a = state->a;
    double *b = state->b;
    double y, w0;

    w0 = x;
    for (n = 1; n < N; n++)
        w0 -= a[n] * w[n];
    w[0] = w0;

    y = 0.0;
    for (n = 0; n < N; n++)
        y += b[n] * w[n];

    for (n = N - 1; n > 0; n--)
        w[n] = w[n - 1];

    return y;
}
