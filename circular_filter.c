#include "circular_filter.h"
#include <stdlib.h>
#include <string.h>

/*
 * cirfltr_create() - allocate and initialize a circular filter
 * N:      length of w
 * Nb:     length of b;
 * b_val:  b values;
 * b_indx: b indices;
 * Na:     length of a;
 * a_val:  a values;
 * a_indx: a indices;
 *
 * Return: the initialized state structure for the filter
 */
struct cirfltr *
cirfltr_create(size_t N, size_t Nb, size_t *b_indx, double *b_val,
               size_t Na, size_t *a_indx, double *a_val)
{
    struct cirfltr *s;
    s = malloc(sizeof(struct cirfltr));
    s->N = N;
    s->Na = Na;
    s->Nb = Nb;
    s->w = calloc(N, sizeof(double));
    s->a_indx = calloc(Na, sizeof(int));
    s->a_val  = calloc(Na, sizeof(double));
    s->b_indx = calloc(Nb, sizeof(int));
    s->b_val  = calloc(Nb, sizeof(double));
    memcpy(s->a_indx, a_indx, Na * sizeof(int));
    memcpy(s->a_val,  a_val,  Na * sizeof(double));
    memcpy(s->b_indx, b_indx, Nb * sizeof(int));
    memcpy(s->b_val,  b_val,  Nb * sizeof(double));
    s->offset = 0;
    return s;
}

/*
 * cirfltr_destroy() - free memory allocated for circular filter
 * s: pointer to filter state
 */
void cirfltr_destroy(struct cirfltr *s)
{
    free(s->b_val);
    free(s->b_indx);
    free(s->a_val);
    free(s->a_indx);
    free(s->w);
    free(s);
}

/*
 * cirfltr_dec() - decrement offset of w buffer (advance delay line by one)
 * s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void cirfltr_dec(struct cirfltr *s)
{
    s->offset--;
    if (s->offset < 0)
        s->offset += s->N;
}

/*
 * cirfltr_inc() - increment offset of w buffer
 * s: pointer to filter state
 *
 * properly wrap offset so that it doesn't fall off the edge of buffer
 */
void cirfltr_inc(struct cirfltr *s)
{
    s->offset++;
    if (s->offset > s->N)
        s->offset -= s->N;
}

/*
 * cirfltr_w() - return pointer to w[n] while handling wrapping
 * s: pointer to filter state
 * n: index into w
 *
 * Return: pointer to w[n]
 */
double * cirfltr_w(struct cirfltr *s, size_t n)
{
    return s->w + ((s->offset + n) % s->N);
}

/*
 * cirfltr_sample() - process one sample through the canonical filter
 * x: input sample to process
 * state: pointer to the state of the filter
 *
 * Return: output sample
 */
float cirfltr_sample(struct cirfltr *fs, float x)
{
    double y;
    double w0;
    size_t n;

    w0 = x;
    for (n = 0; n < fs->Na; n++)
        w0 -= fs->a_val[n] * *cirfltr_w(fs, fs->a_indx[n]);
    *cirfltr_w(fs, 0) = w0;

    y = 0.0;
    for (n = 0; n < fs->Nb; n++)
        y += fs->b_val[n] * *cirfltr_w(fs, fs->b_indx[n]);

    cirfltr_dec(fs);

    return y;
}
