#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? a : b)
#define MIN(a, b) ((a) < (b) ? a : b)
#define NUM_OF_ELEM(x) (sizeof(x)/sizeof(*x))

/* x is length L input array
 * h is length M input array
 * y is length L + M - 1 output array */
void convolve(float y[], float x[], float h[], int L, int M)
{
    int i, k, j;
    for (i = 0; i < L + M - 1; i++) {
        k = MIN(i, M - 1);
        j = MAX(i - M + 1, 0);
        y[i] = 0.0;
        while (j < MIN(i + 1, L)) {
            y[i] += h[k--] * x[j++];
        }
    }
}

void printarray(float x[], int len)
{
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%.3f", i > 0 ? " ":"", x[i]);
    }
    printf("]\n");
}

int main()
{
    float a[] = {1.0, 2.0, 3.0};
    float b[] = {4.0, 5.0};
    float y[4];

    convolve(y, a, b, 3, 2);
    printarray(y, NUM_OF_ELEM(y));
    convolve(y, b, a, 2, 3);
    printarray(y, NUM_OF_ELEM(y));
}
