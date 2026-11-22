/* Magic square for odd n (Coxeter / Siamese rule): 1 goes in the middle
 * of the first row, each next number goes to the upper-left diagonal; if
 * that cell is taken, move one cell down instead.
 * Slide: "Magic Square n = 3". Examples from the notes: n = 3 and n = 5. */
#include <stdio.h>
#define MAX 15  /* not on the slides: row length of the array */

void magic(int n, int sq[][MAX]) {
  int i = 0, j = (n - 1) / 2, s, r, c;
  sq[i][j] = 1;       /* sq must be all zeros */
  for (s = 2; s <= n * n; s++) {
    r = (i - 1 < 0) ? n - 1 : i - 1; /* up */
    c = (j - 1 < 0) ? n - 1 : j - 1; /* left */
    if (sq[r][c]) i = (i + 1) % n; /* down */
    else { i = r; j = c; }
    sq[i][j] = s;
  }
}

/* not on the slides: prints the square and the sum of the first row */
static void print_square(int n, int sq[][MAX]) {
  int i, j, t = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) printf("%3d", sq[i][j]);
    printf("\n");
  }
  for (j = 0; j < n; j++) t += sq[0][j];
  printf("sum = %d\n", t);
}

int main(void) {  /* not on the slides */
  int sq3[MAX][MAX] = {{0}};
  int sq5[MAX][MAX] = {{0}};
  magic(3, sq3);
  print_square(3, sq3);
  magic(5, sq5);
  print_square(5, sq5);
  return 0;
}

/* Expected output:
 *   6  1  8
 *   7  5  3
 *   2  9  4
 * sum = 15
 *  15  8  1 24 17
 *  16 14  7  5 23
 *  22 20 13  6  4
 *   3 21 19 12 10
 *   9  2 25 18 11
 * sum = 65
 */
