/* Passing an array to a function: the array name decays to the address of
 * the first element; print_array() prints the address and value of each
 * element with pointer arithmetic. Slide: "print_array() Step by Step". */
#include <stdio.h>

void print_array(int *p, int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%p %d\n", (void *)(p + i), *(p + i));
}

int main(void) {
  int arr[] = {10, 20, 30, 40};
  print_array(arr, 4);
  return 0;
}

/* The addresses vary on every run; the block below is one sample run and
 * is not expected to match exactly. What does not change: the difference
 * between two consecutive addresses is sizeof(int) = 4 bytes and the
 * values are 10, 20, 30, 40. */
/* Expected output:
 * 00000036C27FFD50 10
 * 00000036C27FFD54 20
 * 00000036C27FFD58 30
 * 00000036C27FFD5C 40
 */
