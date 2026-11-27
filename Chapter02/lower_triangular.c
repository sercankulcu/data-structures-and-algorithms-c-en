/* Storing a lower triangular matrix row by row in a one-dimensional array
 * low: a[i][j] (j <= i) -> k = i(i + 1)/2 + j. Error codes: -1 upper
 * triangle, -2 invalid index. Slides: "read_lower() Step by Step",
 * "lower_index() Step by Step". Example from the notes (Example 2.2):
 * n = 4, input 3 1 4 1 5 9 2 6 5 3. */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: fixed input instead of scanf (stdin is empty) */
static const int input[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
static int consumed = 0;
static void read_int(int *p) { *p = input[consumed++]; }

#define MAX_SIZE 100
void read_lower(int low[], int n) {
  int i, j, k;
  if (n * (n + 1) / 2 > MAX_SIZE) {
    printf("Array too small!\n"); exit(1);
  }
  for (i = 0; i < n; i++) {
    k = (i + 1) * i / 2;      /* before row i */
    for (j = 0; j <= i; j++)  /* j <= i */
      read_int(&low[k + j]);  /* on the slides: scanf("%d", &low[k + j]); */
  }
}

int lower_index(int i, int j, int n) {
  if (i < 0 || i >= n || j < 0 || j >= n) {
    printf("Invalid index\n");
    return -2;
  } else if (i < j) return -1;    /* upper: 0 */
  else return (i + 1) * i / 2 + j;   /* valid */
}

int main(void) {  /* not on the slides (the last three printf calls are from the slide's main) */
  int low[MAX_SIZE], k;
  read_lower(low, 4);
  printf("low:");
  for (k = 0; k < 10; k++) printf(" %d", low[k]);
  printf("\n");

  printf("%d\n", lower_index(2, 1, 4));
  printf("%d\n", lower_index(1, 3, 4));
  printf("%d\n", lower_index(4, 0, 4));
  return 0;
}

/* Expected output:
 * low: 3 1 4 1 5 9 2 6 5 3
 * 4
 * -1
 * Invalid index
 * -2
 */
