/* Band matrix: the a + b - 1 bands around the diagonal are stored in the
 * array band[], starting from the lowest band; start[] holds where each
 * band begins. diag_start() gives the same start by a formula.
 * Slides: "band_build() Step by Step" (and the next one), "band_get()
 * Step by Step", "Analysis and Homework 1". Example from the notes
 * (Example 2.3): n = 4, a = 3, b = 2; input 6 10 3 7 11 1 4 8 12 2 5 9. */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100  /* not on the slides: the limit from the "read_lower" slide */

/* not on the slides: fixed input instead of scanf (stdin is empty) */
static const int input[] = {6, 10, 3, 7, 11, 1, 4, 8, 12, 2, 5, 9};
static int consumed = 0;
static void read_int(int *p) { *p = input[consumed++]; }

void band_build(int band[], int start[],
                int n, int a, int b) {
  int i, k, total = 0;       /* earlier bands */
  if (n*(a+b-1) - a*(a-1)/2 - b*(b-1)/2 > MAX_SIZE) {
    printf("Out of memory!\n"); exit(-1);
  }
  for (i = 1 - a; i <= b - 1; i++) {  /* band by band */
    start[i + a - 1] = total;       /* band start */
    for (k = 0; k <= n - abs(i) - 1; k++)
      read_int(&band[start[i + a - 1] + k]);  /* on the slides: scanf("%d", &band[...]); */
    total += n - abs(i);
  }
}

int band_get(int i, int j, int n, int a,
               int b, int start[]) {
  if (i < 0 || j < 0 || i >= n || j >= n) {
    printf("Index out of range\n"); return -3;
  } else if (j - i >= 1) {         /* upper triangle */
    if (j - i < b)               /* valid band */
      return start[j - i + a - 1] + i;
    else return -1;              /* upper constant */
  } else if (i - j < a)          /* diagonal/lower */
    return start[j - i + a - 1] + j;
  else
    return -2;                   /* lower constant */
}

/* t: band number (1-a..b-1); same as start[t+a-1] */
int diag_start(int t, int n, int a) {
  if (t <= 0)                     /* lower bands */
    return (t + a - 1) * n
           - (a * (a - 1) + t * (1 - t)) / 2;
  return (a - 1) * n - a * (a - 1) / 2  /* start of t=0 */
         + t * n - t * (t - 1) / 2;
}

int main(void) {  /* not on the slides */
  int band[MAX_SIZE], start[MAX_SIZE];
  int n = 4, a = 3, b = 2, i, j, k, t;
  int queries[4][2] = {{3, 1}, {1, 2}, {0, 3}, {3, 0}};

  band_build(band, start, n, a, b);
  printf("start:");
  for (k = 0; k < a + b - 1; k++) printf(" %d", start[k]);
  printf("\nband:");
  for (k = 0; k < 12; k++) printf(" %d", band[k]);
  printf("\n");

  for (k = 0; k < 4; k++) {
    int s = band_get(queries[k][0], queries[k][1], n, a, b, start);
    printf("d%d%d -> %d", queries[k][0], queries[k][1], s);
    if (s >= 0) printf(" (value %d)", band[s]);
    printf("\n");
  }

  printf("diag_start:");
  for (t = 1 - a; t <= b - 1; t++) printf(" %d", diag_start(t, n, a));
  printf("\n");

  printf("matrix (0 outside the band):\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      int s = band_get(i, j, n, a, b, start);
      printf("%3d", s >= 0 ? band[s] : 0);
    }
    printf("\n");
  }
  return 0;
}

/* Expected output:
 * start: 0 2 5 9
 * band: 6 10 3 7 11 1 4 8 12 2 5 9
 * d31 -> 1 (value 10)
 * d12 -> 10 (value 5)
 * d03 -> -1
 * d30 -> -2
 * diag_start: 0 2 5 9
 * matrix (0 outside the band):
 *   1  2  0  0
 *   3  4  5  0
 *   6  7  8  9
 *   0 10 11 12
 */
