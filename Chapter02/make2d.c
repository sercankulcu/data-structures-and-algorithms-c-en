/* Two-dimensional dynamic array: first the row pointers, then each row
 * with its own malloc; if a row cannot be allocated, the earlier ones are
 * freed. Slide: "make2d() Step by Step". Example from the notes:
 * make2d(3, 4), x[i][j] = 10i + j; x[2][3] = 23 and *(*(x + 1) + 2) = 12. */
#include <stdio.h>
#include <stdlib.h>

int **make2d(int rows, int cols) {
  int i, **x = malloc(rows * sizeof *x);
  if (x == NULL) return NULL;
  for (i = 0; i < rows; i++) {
    x[i] = malloc(cols * sizeof **x);
    if (x[i] == NULL) {                /* undo */
      while (--i >= 0) free(x[i]);
      free(x); return NULL;
    }
  }
  return x;
}

/* not on the slides: frees the rows first, then the pointer array */
static void free2d(int **x, int rows) {
  int i;
  for (i = 0; i < rows; i++) free(x[i]);
  free(x);
}

int main(void) {  /* not on the slides */
  int i, j, **x = make2d(3, 4);
  if (x == NULL) {
    printf("Out of memory\n");
    return 1;
  }
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
      x[i][j] = 10 * i + j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) printf("%3d", x[i][j]);
    printf("\n");
  }
  printf("x[2][3] = %d\n", x[2][3]);
  printf("*(*(x + 1) + 2) = %d\n", *(*(x + 1) + 2));
  free2d(x, 3);
  return 0;
}

/* Expected output:
 *   0  1  2  3
 *  10 11 12 13
 *  20 21 22 23
 * x[2][3] = 23
 * *(*(x + 1) + 2) = 12
 */
