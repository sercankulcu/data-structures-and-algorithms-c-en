/* Space complexity examples: abc(), which uses only fixed memory, the
 * iterative sum(), and the recursive rsum(), which opens a stack frame on
 * every call.
 * Slides: "Space Complexity", "sum and rsum: Memory".
 * Example from the notes: abc(1, 2, 3) and list = {3, 1, 4}. */
#include <stdio.h>

float abc(float a, float b, float c) {
  return a + b + b * c
         + (a + b - c) / (a + b) + 4.00;
}
/* fixed space only: S_abc(I) = 0 */

float sum(float list[], int n) {
  float tempsum = 0;
  int i;
  for (i = 0; i < n; i++)
    tempsum += list[i];
  return tempsum;
}

float rsum(float list[], int n) {
  if (n)
    return rsum(list, n - 1) + list[n - 1];
  return 0;
}

int main(void) {  /* not on the slides */
  float list[] = {3, 1, 4};
  printf("abc(1, 2, 3) = %.2f\n", abc(1, 2, 3));
  printf("sum = %.2f\n", sum(list, 3));
  printf("rsum = %.2f\n", rsum(list, 3));
  return 0;
}

/* Expected output:
 * abc(1, 2, 3) = 13.00
 * sum = 8.00
 * rsum = 8.00
 */
