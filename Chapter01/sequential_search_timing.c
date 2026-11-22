/* Repeated timing: the fast seqsearch() is run runtimes[i] times for each
 * size and the total time is divided by the repeat count (microseconds
 * per search).
 * Slide: "Application 2: Sequential Search" (timing part). The program
 * around that part (arrays, loops, printing) is not on the slides; the
 * repeat counts are large for small sizes (500000) and small for large
 * sizes (5000), as explained in the notes. */
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 5001  /* not on the slides: 5000 elements + sentinel */

/* not on the slides: seqsearch() from the "Application 2" slide */
int seqsearch(int list[], int searchnum, int n) {
  int i;
  list[n] = searchnum;          /* sentinel */
  for (i = 0; list[i] != searchnum; i++)
    ;
  return (i < n) ? i : -1;
}

int main(void) {  /* not on the slides: the program wrapping the timing part */
  int i, j, pos = 0, list[MAX_SIZE];
  int sizelist[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
    200, 400, 600, 800, 1000, 2000, 3000, 4000, 5000 };
  long runtimes[] = { 500000, 500000, 500000, 300000, 250000, 200000,
    160000, 140000, 120000, 110000, 100000, 50000, 25000, 16000, 12000,
    10000, 10000, 8000, 6000, 5000 };
  clock_t start, stop;
  double total, avg;
  for (j = 0; j < MAX_SIZE; j++)
    list[j] = j;                    /* -1 is never found: always the worst case */
  for (i = 0; i < 20; i++) {
    /* the part on the slides: */
    start = clock();
    for (j = 0; j < runtimes[i]; j++)
      pos = seqsearch(list, -1, sizelist[i]);
    stop = clock();
    total = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
    avg = 1000.0 * total / runtimes[i];  /* in us */
    list[sizelist[i]] = sizelist[i];  /* undo the sentinel */
    /* end of that part */
    printf("%4d elements: pos = %d, %8.3f us / search\n", sizelist[i], pos, avg);
  }
  return 0;
}

/* Timings vary with the machine and the run; the block below is one sample
 * run and is not expected to match exactly. What does not change: 20 lines,
 * pos is always -1, and the time per search grows linearly with n. */
/* Expected output:
 *    0 elements: pos = -1,    0.000 us / search
 *   10 elements: pos = -1,    0.008 us / search
 *   20 elements: pos = -1,    0.018 us / search
 *   30 elements: pos = -1,    0.037 us / search
 *   40 elements: pos = -1,    0.036 us / search
 *   50 elements: pos = -1,    0.075 us / search
 *   60 elements: pos = -1,    0.075 us / search
 *   70 elements: pos = -1,    0.107 us / search
 *   80 elements: pos = -1,    0.067 us / search
 *   90 elements: pos = -1,    0.109 us / search
 *  100 elements: pos = -1,    0.130 us / search
 *  200 elements: pos = -1,    0.160 us / search
 *  400 elements: pos = -1,    0.280 us / search
 *  600 elements: pos = -1,    0.500 us / search
 *  800 elements: pos = -1,    0.500 us / search
 * 1000 elements: pos = -1,    0.700 us / search
 * 2000 elements: pos = -1,    1.400 us / search
 * 3000 elements: pos = -1,    3.500 us / search
 * 4000 elements: pos = -1,    3.500 us / search
 * 5000 elements: pos = -1,    3.800 us / search
 */
