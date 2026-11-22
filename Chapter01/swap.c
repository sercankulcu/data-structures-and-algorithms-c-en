/* Two forms of swapping: the SWAP macro and a swap() function taking
 * pointers. Slides: "SWAP: Macro and Function" (two blocks), "swap() Step
 * by Step". Example: a = 3, b = 8 (slide) and the swap in the first pass
 * of selection sort (list[0] and list[1] of the notes' array
 * {29, 10, 14, 37, 13}). */
#include <stdio.h>

#define SWAP(x, y, t) \
        ((t) = (x), (x) = (y), (y) = (t))

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

/* not on the slides: helper that prints the array */
static void print_array(const int list[], int n) {
  int k;
  for (k = 0; k < n; k++) printf("%d ", list[k]);
  printf("\n");
}

int main(void) {
  int a = 3, b = 8;
  int list[] = {29, 10, 14, 37, 13};  /* not on the slides: example array */
  int i = 0, min = 1;                 /* not on the slides: indices of the first pass */
  swap(&a, &b);
  printf("%d %d\n", a, b);

  {
    int temp;
    SWAP(list[i], list[min], temp);
  }
  print_array(list, 5);           /* not on the slides */

  swap(&list[i], &list[min]);     /* the same swap with the function: undoes it */
  print_array(list, 5);           /* not on the slides */
  return 0;                       /* not on the slides */
}

/* The pitfall of the macro (explained in the notes, not run here):
 * SWAP(a[i++], a[j], t) evaluates i++ twice and breaks the swap. */

/* Expected output:
 * 8 3
 * 10 29 14 37 13
 * 29 10 14 37 13
 */
