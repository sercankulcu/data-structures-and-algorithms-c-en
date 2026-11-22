/* Generating permutations by swapping: each remaining element is brought
 * to position i in turn, and the swap is undone after the recursive call.
 * Slides: "perm("abc") Step by Step" and the following one. */
#include <stdio.h>  /* not on the slides */

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  /* not on the slides: the macro from Chapter 1 */

void perm(char *list, int i, int n) {
  int j, temp;
  if (i == n) {                  /* one arrangement */
    for (j = 0; j < n; j++) printf("%c", list[j]);
    printf("\n");
  } else
    for (j = i; j < n; j++) {
      SWAP(list[i], list[j], temp);
      perm(list, i + 1, n);
      SWAP(list[i], list[j], temp);
    }
}

int main(void) {  /* not on the slides */
  char list[] = "abc";           /* must be a modifiable array */
  perm(list, 0, 3);
  printf("final state: %s\n", list);
  return 0;
}

/* Expected output:
 * abc
 * acb
 * bac
 * bca
 * cba
 * cab
 * final state: abc
 */
