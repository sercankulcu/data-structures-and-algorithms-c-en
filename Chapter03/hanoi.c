/* Towers of Hanoi: move n - 1 disks to the middle peg, the largest to the
 * target, then n - 1 disks to the target. 2^n - 1 moves.
 * Slide: "Hanoi n = 3 Step by Step". */
#include <stdio.h>  /* not on the slides */

void hanoi(int n, char *from, char *via,
           char *to) {
  if (n == 1)
    printf("%s -> %s\n", from, to);
  else {
    hanoi(n - 1, from, to, via);
    printf("%s -> %s\n", from, to);
    hanoi(n - 1, via, from, to);
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
