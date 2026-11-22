/* Counting program steps with a global count variable: sum() takes
 * 2n + 3 steps, rsum() takes 2n + 2.
 * Slides: "sum() with a Step Counter", "rsum() and the Call Stack".
 * Example from the notes: list = {3, 1, 4}, n = 3 (count 9 and 8). */
#include <stdio.h>

int count = 0;  /* not on the slides: the counter declaration */

float sum(float list[], int n) {
  float tempsum = 0; count++;
  int i;
  for (i = 0; i < n; i++) {
    count++;             /* loop test */
    tempsum += list[i]; count++;
  }
  count++;  /* last loop test */
  count++;  return tempsum;
}

float rsum(float list[], int n) {
  count++;               /* if test */
  if (n) {
    count++;             /* add + return */
    return rsum(list, n - 1) + list[n - 1];
  }
  count++;
  return 0;
}

int main(void) {  /* not on the slides */
  float list[] = {3, 1, 4};
  float s;
  int n;

  count = 0;
  s = sum(list, 3);
  printf("sum = %.2f, count = %d\n", s, count);

  count = 0;
  s = rsum(list, 3);
  printf("rsum = %.2f, count = %d\n", s, count);

  for (n = 0; n <= 3; n++) {     /* check the formulas */
    count = 0; sum(list, n);
    printf("n = %d: sum %d steps, ", n, count);
    count = 0; rsum(list, n);
    printf("rsum %d steps\n", count);
  }
  return 0;
}

/* Expected output:
 * sum = 8.00, count = 9
 * rsum = 8.00, count = 8
 * n = 0: sum 3 steps, rsum 2 steps
 * n = 1: sum 5 steps, rsum 4 steps
 * n = 2: sum 7 steps, rsum 6 steps
 * n = 3: sum 9 steps, rsum 8 steps
 */
