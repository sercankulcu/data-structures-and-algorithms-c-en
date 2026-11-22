/* Byte address of an element of a two-dimensional array in row-major
 * order: alpha + (i * dim1 + j) * s. Slide: "address() Step by Step".
 * int x[3][4], alpha = 100, s = 4: x[1][2] -> 124, x[2][3] -> 144. */
#include <stdio.h>  /* not on the slides */

/* int x[3][4]: row-major byte address */
long address(long alpha, int i, int j,
             int dim1, int s) {
  long k = (long)i * dim1 + j;   /* elements before */
  return alpha + k * s;
}

int main(void) {
  printf("%ld\n", address(100, 1, 2, 4, 4));
  printf("%ld\n", address(100, 2, 3, 4, 4));
  return 0;
}

/* Expected output:
 * 124
 * 144
 */
