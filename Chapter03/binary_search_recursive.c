/* Recursive binary search: two base cases (empty range, found) and two
 * tail calls. Slides: "Recursive Binary Search" and "... Step by Step".
 * The test array is from the notes; 18 and 25 are searched. */
#include <stdio.h>  /* not on the slides */

#define COMPARE(x, y) ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)  /* not on the slides: from the "The Binary Search Problem" slide */

int binsearch(int list[], int x, int l, int r) {
  int m;
  if (l > r) return -1;          /* empty range */
  m = (l + r) / 2;
  switch (COMPARE(list[m], x)) {
    case -1: return binsearch(list, x, m + 1, r);
    case 0:  return m;
    case 1:  return binsearch(list, x, l, m - 1);
  }
  return -1;                     /* unreachable */
}

int main(void) {  /* not on the slides */
  int list[] = {4, 13, 18, 19, 24, 27, 33, 36, 39, 40};
  printf("18 -> %d\n", binsearch(list, 18, 0, 9));
  printf("25 -> %d\n", binsearch(list, 25, 0, 9));
  return 0;
}

/* Expected output:
 * 18 -> 2
 * 25 -> -1
 */
