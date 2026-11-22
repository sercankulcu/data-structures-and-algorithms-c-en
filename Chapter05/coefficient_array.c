/* Representation 1 of a polynomial: the coefficient array. coef[i] is the
 * coefficient of x^i; zero coefficients are stored too. Example from the notes:
 * P(x) = 5x^100: only one of 101 cells is meaningful and the structure takes
 * 408 bytes.
 * Slide: "Method 1 (Bad): Keep Every Coefficient". */
#include <stdio.h>

#define MAX_DEGREE 101   /* max degree + 1 */
typedef struct {
  int degree;               /* largest exponent */
  float coef[MAX_DEGREE];   /* coef[i]: coefficient of x^i */
} polynomial;
polynomial P;

int main(void)
{
    int i, zeros = 0;
    P.degree = 100;                       /* P is global: coef[] starts zeroed */
    P.coef[100] = 5;
    for (i = P.degree; i >= 0; i--) {
        if (P.coef[i] != 0) printf("%gx^%d\n", P.coef[i], i);
        else zeros++;
    }
    printf("zero cells: %d / %d\n", zeros, MAX_DEGREE);
    printf("sizeof(P) = %zu bytes\n", sizeof P);
    return 0;
}

/* Note: Linux x86-64: int and float are 4 bytes. */
/* Expected output:
 * 5x^100
 * zero cells: 100 / 101
 * sizeof(P) = 408 bytes
 */
