/* n stacks in a single memory array: stack i uses the segment
 * memory[boundary[i]+1 .. boundary[i+1]]; empty: top[i] == boundary[i], full:
 * top[i] == boundary[i+1]. Example from the notes: m = 12, n = 3,
 * top = boundary = [-1, 3, 7], boundary[3] = 11. The seventh call push(0, 6) is
 * rejected, although six cells of memory are free.
 * Slide: "Code Trace: n Stacks, One Memory". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: global memory, top and boundary arrays */
#define M 12                 /* size of memory */
#define N 3                  /* number of stacks */
int memory[M];
int top[N];
int boundary[N + 1];

/* stack i: boundary[i]+1 .. boundary[i+1] */
bool push(int i, int x) {
  if (top[i] == boundary[i + 1]) return false; /* full */
  memory[++top[i]] = x;
  return true;
}
bool pop(int i, int *x) {
  if (top[i] == boundary[i]) return false;     /* empty */
  *x = memory[top[i]--];
  return true;
}

/* not on the slides: prints the top array */
static void print_top(void) {
  printf("top = [%d, %d, %d]\n", top[0], top[1], top[2]);
}

int main(void)
{
  int i, x;
  int which[] = {0, 1, 0, 2, 0, 0, 0};
  int values[] = {5, 7, 9, 4, 2, 8, 6};
  for (i = 0; i < N; i++)                 /* equal segments, all empty */
    top[i] = boundary[i] = (M / N) * i - 1;
  boundary[N] = M - 1;
  printf("boundary = [%d, %d, %d, %d], ", boundary[0], boundary[1], boundary[2], boundary[3]);
  print_top();
  for (i = 0; i < 7; i++) {
    bool ok = push(which[i], values[i]);
    printf("push(%d, %d): %-5s ", which[i], values[i], ok ? "true" : "false");
    print_top();
  }
  if (pop(1, &x)) printf("pop(1, &x): true, x = %d ", x);
  print_top();
  printf("pop(1, &x) again: %s\n", pop(1, &x) ? "true" : "false");
  return 0;
}

/* Note: two spaces after "true", one after "false". */
/* Expected output:
 * boundary = [-1, 3, 7, 11], top = [-1, 3, 7]
 * push(0, 5): true  top = [0, 3, 7]
 * push(1, 7): true  top = [0, 4, 7]
 * push(0, 9): true  top = [1, 4, 7]
 * push(2, 4): true  top = [1, 4, 8]
 * push(0, 2): true  top = [2, 4, 8]
 * push(0, 8): true  top = [3, 4, 8]
 * push(0, 6): false top = [3, 4, 8]
 * pop(1, &x): true, x = 7 top = [3, 3, 8]
 * pop(1, &x) again: false
 */
