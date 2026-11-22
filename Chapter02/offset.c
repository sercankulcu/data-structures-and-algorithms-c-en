/* Relative position of an element in an n-dimensional array, by Horner's
 * method: t = (...((i0 * u1 + i1) * u2 + i2) ...). Slide: "offset() Step
 * by Step". Example from the notes: in G[2][2][3], G[1][0][2] -> 8. */
#include <stdio.h>  /* not on the slides */

/* idx: indices, dim: sizes, n: dimensions */
int offset(const int idx[], const int dim[], int n) {
  int j, t = idx[0];
  for (j = 1; j < n; j++)
    t = t * dim[j] + idx[j];            /* Horner */
  return t;               /* address = alpha + t*s */
}

int main(void) {  /* not on the slides */
  int G[2][2][3];
  int idx[] = {1, 0, 2}, dim[] = {2, 2, 3};
  printf("offset = %d\n", offset(idx, dim, 3));
  /* the same position in a real array: byte difference / sizeof(int) */
  printf("&G[1][0][2] - &G[0][0][0] = %d\n",
         (int)(((char *)&G[1][0][2] - (char *)G) / (int)sizeof(int)));
  return 0;
}

/* Expected output:
 * offset = 8
 * &G[1][0][2] - &G[0][0][0] = 8
 */
