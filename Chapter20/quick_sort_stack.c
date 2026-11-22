/* Non-recursive quicksort (quicksort2): pending (L, R) jobs are kept on an
 * explicit stack implemented with an array; the larger piece is pushed first,
 * so the smaller piece is always processed and the stack stays O(lg n). The
 * example is [4, 7, 2, 6, 1, 5, 3] from the notes.
 * Slides: "Non-Recursive Quicksort (quicksort2)" (two slides), "Code Trace:
 * quicksort2()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from Chapter 19 "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* on the slides it is on the second slide; must be defined before quicksort2 */
#define YMAX 64     /* > 2*lg n */
static int stack[YMAX], top;
void stack_init(void) { top = 0; }
int stack_empty(void) { return top == 0; }
void push(int x) { stack[top++] = x; }
int pop(void) { return stack[--top]; }
#define push_range(A, B) \
  do { push(B); push(A); } while (0)

/* not on the slides: partition from "Partitioning Invariant" slide */
int partition(int a[], int L, int R) {
    int i = L - 1, j = R, v = a[R]; // pivot a[R]
    for (;;) {
        while (less(a[++i], v))
            ;
        while (less(v, a[--j]))
            if (j == L) break;
        if (i >= j) break;
        SWAP(a[i], a[j]);
    }
    SWAP(a[i], a[R]);
    return i;
}

void quicksort2(int a[], int L, int R) {
  stack_init(); push_range(L, R);
  while (!stack_empty()) {
    L = pop(); R = pop();
    if (R <= L) continue;
    int i = partition(a, L, R);
    if (i - L > R - i) {       // larger part first
      push_range(L, i - 1); push_range(i + 1, R);
    } else {
      push_range(i + 1, R); push_range(L, i - 1);
    }
  }
}

int main(void) {   /* not on the slides */
    int a[] = {4, 7, 2, 6, 1, 5, 3};
    quicksort2(a, 0, 6);
    for (int i = 0; i < 7; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 1 2 3 4 5 6 7 
 */
