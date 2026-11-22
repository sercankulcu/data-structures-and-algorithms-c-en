/* The first recursion example: base case n <= 1, step n * fact(n - 1).
 * Slide: "fact(3) Step by Step". */
#include <stdio.h>  /* not on the slides */

long fact(int n) {
  if (n <= 1)
    return 1;              /* base case */
  return n * fact(n - 1);
}

int main(void) {
  printf("%ld\n", fact(3));
  return 0;
}

/* Expected output:
 * 6
 */
