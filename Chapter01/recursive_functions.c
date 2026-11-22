/* Recursive functions: factorial, Fibonacci and the binomial coefficient
 * (Pascal's triangle recurrence). Slide: "Homework Answers".
 * Examples from the notes: fact(5), fact(10), fib(10), binom(5, 2),
 * binom(10, 3). */
#include <stdio.h>

long fact(long n) {
  if (n <= 1) return 1;
  return n * fact(n - 1);
}

long fib(long n) {
  if (n <= 1) return n;   /* f0 = 0, f1 = 1 */
  return fib(n - 1) + fib(n - 2);
}

long binom(int n, int m) {
  if (m == 0 || m == n) return 1;
  return binom(n - 1, m) + binom(n - 1, m - 1);
}

int main(void) {  /* not on the slides */
  printf("fact(5) = %ld\n", fact(5));
  printf("fact(10) = %ld\n", fact(10));
  printf("fib(10) = %ld\n", fib(10));
  printf("binom(5, 2) = %ld\n", binom(5, 2));
  printf("binom(10, 3) = %ld\n", binom(10, 3));
  return 0;
}

/* Expected output:
 * fact(5) = 120
 * fact(10) = 3628800
 * fib(10) = 55
 * binom(5, 2) = 10
 * binom(10, 3) = 120
 */
