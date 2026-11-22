/* Timing selection sort with clock() on descending arrays of 0..5000
 * elements. Slide: "Application 1: Timing a Sort". sort() and SWAP are
 * taken from the "Selection Sort: C Code" slide. */
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 5001
#define ITERATIONS 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  /* not on the slides: from the previous slide */
void sort(int list[], int n);   /* selection sort */

int main(void) {
  int i, j, list[MAX_SIZE];
  int sizelist[] = { 0, 100, 300, 600, 900, 1200, 1500, 2000,
    3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800,
    3900, 4000, 5000 };
  clock_t start, stop;  double ms;
  for (i = 0; i < ITERATIONS; i++) {
    for (j = 0; j < sizelist[i]; j++)
      list[j] = sizelist[i] - j;   /* descending */
    start = clock();
    sort(list, sizelist[i]);
    stop = clock();
    ms = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
    printf("%4d elements: %6.1f ms\n", sizelist[i], ms);
  }
  return 0;
}

/* not on the slides: sort() from the "Selection Sort: C Code" slide */
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

/* Timings vary with the machine and the run; the block below is one sample
 * run (Windows, clock() ticks of 1 ms) and is not expected to match
 * exactly. What does not change: 20 lines, the first line is 0.0 ms, and
 * the time grows quadratically with n. */
/* Expected output:
 *    0 elements:    0.0 ms
 *  100 elements:    0.0 ms
 *  300 elements:    0.0 ms
 *  600 elements:    0.0 ms
 *  900 elements:    1.0 ms
 * 1200 elements:    0.0 ms
 * 1500 elements:    1.0 ms
 * 2000 elements:    2.0 ms
 * 3000 elements:    3.0 ms
 * 3100 elements:   13.0 ms
 * 3200 elements:    9.0 ms
 * 3300 elements:   11.0 ms
 * 3400 elements:    9.0 ms
 * 3500 elements:    8.0 ms
 * 3600 elements:   13.0 ms
 * 3700 elements:    8.0 ms
 * 3800 elements:   12.0 ms
 * 3900 elements:   12.0 ms
 * 4000 elements:   16.0 ms
 * 5000 elements:   41.0 ms
 */
