/* Iterative binary search and the three-way COMPARE macro. The range is
 * [left, right], closed at both ends; half of it is discarded in every
 * round. Slides: "The Binary Search Problem", "Binary Search: Looking for
 * 18", "Binary Search: 25 Is Missing". The test array is from the notes. */
#include <stdio.h>  /* not on the slides */

#define COMPARE(x, y) ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)

int binsearch(int list[], int searchnum,
              int left, int right) {
  while (left <= right) {
    int middle = (left + right) / 2;
    switch (COMPARE(list[middle], searchnum)) {
      case -1: left = middle + 1; break;
      case 0: return middle;
      case 1: right = middle - 1;
    }
  }
  return -1;
}

int main(void) {  /* not on the slides */
  int list[] = {4, 13, 18, 19, 24, 27, 33, 36, 39, 40};
  printf("18 -> %d\n", binsearch(list, 18, 0, 9));
  printf("25 -> %d\n", binsearch(list, 25, 0, 9));
  printf("4 -> %d\n", binsearch(list, 4, 0, 9));
  printf("40 -> %d\n", binsearch(list, 40, 0, 9));
  return 0;
}

/* Expected output:
 * 18 -> 2
 * 25 -> -1
 * 4 -> 0
 * 40 -> 9
 */
