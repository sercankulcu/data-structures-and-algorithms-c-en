/* Towers of Hanoi: move n - 1 disks to the middle peg, the largest to the
 * target, then n - 1 disks to the target. 2^n - 1 moves.
 * Slide: "Hanoi n = 3 Step by Step". */
#include <stdio.h>  /* not on the slides */

void hanoi(int n, char *src, char *aux,
           char *dst) {
  if (n == 1)
    printf("%s -> %s\n", src, dst);
  else {
    hanoi(n - 1, src, dst, aux);
    printf("%s -> %s\n", src, dst);
    hanoi(n - 1, aux, src, dst);
  }
}

int main(void) {  /* not on the slides */
  /* main: */ hanoi(3, "A", "B", "C");
  return 0;
}

/* Expected output:
 * A -> C
 * A -> B
 * C -> B
 * A -> C
 * B -> A
 * B -> C
 * A -> C
 */
