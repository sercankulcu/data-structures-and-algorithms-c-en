/* Selection sort and the SWAP macro. In each pass the smallest element of
 * list[i..n-1] is swapped with list[i].
 * Slides: "Selection Sort: C Code" (two blocks), "Faulty sort() Version"
 * (in a comment only). Example array from the notes: {29, 10, 14, 37, 13}. */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int list[], int n);

int main(void) {
  int i, n, list[MAX_SIZE];
  int example[] = {29, 10, 14, 37, 13};  /* not on the slides: the example from the notes */
  /* on the slides: printf("Enter the array size: ");
   *                if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) ...
   * There is no keyboard input here; n is given as a constant. */
  n = 5;
  if (n < 1 || n > MAX_SIZE) {
    printf("Invalid value of n!\n");
    return 1;
  }
  /* on the slides: list[i] = rand() % 100; here the example from the notes is used */
  for (i = 0; i < n; i++) list[i] = example[i];
  sort(list, n);
  for (i = 0; i < n; i++) printf("%d ", list[i]);
  printf("\n");  /* not on the slides */
  return 0;
}

void sort(int list[], int n) {
  int i, j, min, temp;
  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (list[j] < list[min])
        min = j;
    SWAP(list[i], list[min], temp);
  }
}

/* The faulty version from the slide (not run). It still sorts the array
 * but is not selection sort: the inner loop starts at j = 0, it looks for
 * the largest element with >, and the swap is done inside the inner loop.
 * For {29, 10, 14, 37, 13} it makes 25 comparisons and 7 swaps (the
 * correct version: 10 and 3).
 *
 * void sort(int list[], int n) {
 *   int i, j, min, temp;
 *   for (i = 0; i < n; i++) {
 *     min = i;
 *     for (j = 0; j < n; j++)
 *       if (list[j] > list[min]) {
 *         min = j;
 *         SWAP(list[i], list[min], temp);
 *       }
 *   }
 * }
 */

/* Expected output:
 * 10 13 14 29 37
 */
