/* Sequential search with a sentinel: the search value is stored in
 * list[n], so the loop needs no bounds check. The array must have room
 * for n + 1 elements.
 * Slides: "Application 2: Sequential Search", "seqsearch() Step by Step".
 * Example from the notes: list = {4, 8, 2}; search 5 (-1), search 8 (1). */
#include <stdio.h>

int seqsearch(int list[], int searchnum, int n) {
  int i;
  list[n] = searchnum;          /* sentinel */
  for (i = 0; list[i] != searchnum; i++)
    ;
  return (i < n) ? i : -1;
}

int main(void) {  /* not on the slides */
  int list[4] = {4, 8, 2};      /* 3 elements + room for the sentinel */
  printf("seqsearch(list, 5, 3) = %d\n", seqsearch(list, 5, 3));
  printf("seqsearch(list, 8, 3) = %d\n", seqsearch(list, 8, 3));
  return 0;
}

/* Expected output:
 * seqsearch(list, 5, 3) = -1
 * seqsearch(list, 8, 3) = 1
 */
