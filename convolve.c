#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)

/* x: input samples of length L
 * h: filter impulse response of length M
 * y: output samples of length L + M - 1 */
float *convolve(const float *x, int L, const float *h, int M, float *y)
{
    int i, j, k;
    double acc;

    for (i = 0; i < L + M - 1; i++) {
        k = MIN(i, M - 1);
        j = MAX(i - M + 1, 0);
        for (acc = 0.0; j < MIN(i + 1, L); j++, k--) {
            acc += h[k] * x[j];
        }
        y[i] = acc;
    }

    return y;
}

void printarray(const char *label, const float *x, int len)
{
    int i;
    printf("[");
    for (i = 0; i < len; i++) {
        printf("%s%.3f", i > 0 ? " ":"", x[i]);
    }
    printf("]\n");
}

void it_commutes(void)
{
    float x[] = {1.0, 2.0, 3.0};
    float h[] = {4.0, 5.0};
    float y[4];

    printf("the convolution operator is commutative:\n");
    printarray("x * h", convolve(x, 3, h, 2, y), 4);
    printarray("h * x", convolve(h, 2, x, 3, y), 4);
}

int main()
{
    it_commutes();

    return 0;
}
