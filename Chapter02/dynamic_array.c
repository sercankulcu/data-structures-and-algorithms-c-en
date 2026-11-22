/* Dynamic array: append() doubles the capacity with realloc when full.
 * The result of realloc is first stored in a temporary t; on failure the
 * old block is not lost.
 * Slide: "append() Step by Step". Example from the notes (Example 2.1):
 * 7, 3, 9, 4, 6 are appended to an empty array. */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int *data; int size, cap; } DynArray;

int append(DynArray *d, int x) {
  if (d->size == d->cap) {               /* full */
    int ncap = d->cap ? 2 * d->cap : 1;
    int *t = realloc(d->data, ncap * sizeof *t);
    if (t == NULL) return 0;    /* old block intact */
    d->data = t;
    d->cap = ncap;
  }
  d->data[d->size++] = x;
  return 1;
}

int main(void) {  /* not on the slides */
  DynArray d = {NULL, 0, 0};
  int x[] = {7, 3, 9, 4, 6};
  int i, k;
  for (i = 0; i < 5; i++) {
    if (!append(&d, x[i])) {
      printf("out of memory\n");
      break;
    }
    printf("x = %d: size = %d, cap = %d, data = [", x[i], d.size, d.cap);
    for (k = 0; k < d.size; k++)
      printf(k ? ", %d" : "%d", d.data[k]);
    printf("]\n");
  }
  free(d.data);   /* not on the slides: give the array back */
  return 0;
}

/* Expected output:
 * x = 7: size = 1, cap = 1, data = [7]
 * x = 3: size = 2, cap = 2, data = [7, 3]
 * x = 9: size = 3, cap = 4, data = [7, 3, 9]
 * x = 4: size = 4, cap = 4, data = [7, 3, 9, 4]
 * x = 6: size = 5, cap = 8, data = [7, 3, 9, 4, 6]
 */
