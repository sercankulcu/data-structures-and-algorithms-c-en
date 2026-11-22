/* Three forms of factorial: recursive, iterative, and tail recursive with
 * an accumulator parameter. Slides: "Recursion and Loops", "Tail
 * Recursion". Example from the notes: fact_tail(4, 1) -> 24. */
#include <stdio.h>  /* not on the slides */

/* recursive */
long fact(int n) {
  return n <= 1 ? 1 : n * fact(n - 1);
}

/* iterative */
long fact_iter(int n) {
  long f = 1;
  while (n > 1)
    f *= n--;
  return f;
}

long fact_tail(int n, long acc) {
  if (n <= 1) return acc;
  return fact_tail(n - 1, n * acc);  /* last: call */
}
/* first call: fact_tail(n, 1) */

int main(void) {  /* not on the slides */
  int example[] = {0, 1, 4, 10};
  int k;
  for (k = 0; k < 4; k++) {
    int n = example[k];
    printf("n = %d: fact %ld, fact_iter %ld, fact_tail %ld\n",
           n, fact(n), fact_iter(n), fact_tail(n, 1));
  }
  return 0;
}

/* Expected output:
 * n = 0: fact 1, fact_iter 1, fact_tail 1
 * n = 1: fact 1, fact_iter 1, fact_tail 1
 * n = 4: fact 24, fact_iter 24, fact_tail 24
 * n = 10: fact 3628800, fact_iter 3628800, fact_tail 3628800
 */
