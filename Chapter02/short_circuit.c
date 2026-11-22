/* Left-to-right, short-circuit evaluation of &&: if i < n is false,
 * a[i] is never read; the two forms are equivalent.
 * Slide: "&& Evaluation Order". */
#include <stdio.h>

int main(void) {  /* not on the slides */
  int a[] = {5, 0, 7};
  int n = 3, i;
  for (i = 0; i <= n; i++) {        /* a[n] must not be read when i = n */
    /* 1 */ if (i < n && a[i] != 0) printf("1: a[%d] = %d\n", i, a[i]);

    /* 2 */ if (i < n)
              if (a[i] != 0) printf("2: a[%d] = %d\n", i, a[i]);
  }
  printf("a[%d] was never read\n", n);
  return 0;
}

/* Expected output:
 * 1: a[0] = 5
 * 2: a[0] = 5
 * 1: a[2] = 7
 * 2: a[2] = 7
 * a[3] was never read
 */
