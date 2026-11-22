/* The n-queens problem by backtracking: q[r] is the column of the queen in
 * row r; is_safe() checks for a clash in the same column or on a diagonal,
 * place() tries row by row and returns at a dead end. Slides: "The
 * n-Queens Problem", "4-Queens Step by Step". Examples from the notes: the
 * first solution for n = 4 and n = 8. */
#include <stdio.h>
#include <stdlib.h>  /* not on the slides: abs */

int q[8];  /* q[r]: column of the queen in row r */

int is_safe(int r, int c) {
  int i;
  for (i = 0; i < r; i++)
    if (q[i] == c || abs(q[i] - c) == r - i)
      return 0;         /* same column or diagonal */
  return 1;
}

int place(int r, int n) {
  int c;
  if (r == n) return 1;             /* solved */
  for (c = 0; c < n; c++)
    if (is_safe(r, c)) {
      q[r] = c;
      if (place(r + 1, n)) return 1;
    }
  return 0;                  /* backtrack */
}

/* not on the slides: prints the solution as an array and as a board */
static void print_solution(int n) {
  int r, c;
  printf("q =");
  for (r = 0; r < n; r++) printf(" %d", q[r]);
  printf("\n");
  for (r = 0; r < n; r++) {
    for (c = 0; c < n; c++) printf("%c", q[r] == c ? 'Q' : '.');
    printf("\n");
  }
}

int main(void) {  /* not on the slides */
  if (place(0, 4)) print_solution(4);
  if (place(0, 8)) print_solution(8);
  return 0;
}

/* Expected output:
 * q = 1 3 0 2
 * .Q..
 * ...Q
 * Q...
 * ..Q.
 * q = 0 4 7 5 2 6 1 3
 * Q.......
 * ....Q...
 * .......Q
 * .....Q..
 * ..Q.....
 * ......Q.
 * .Q......
 * ...Q....
 */
