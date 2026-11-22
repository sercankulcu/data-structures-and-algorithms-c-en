/* Triple (row, column, value) representation of a sparse matrix and the
 * simple transpose: for each column of M all triples are examined; the result
 * is automatically in row order. M[0] is the header: number of rows, number of
 * columns, number of nonzero entries.
 * Examples from the notes: a 3 x 4 matrix (4 entries) and a 6 x 6 matrix
 * (8 entries).
 * Slides: "The Triple Table, and When It Pays Off", "transpose: Scan Every Term
 * for Each Column". */
#include <stdio.h>

#define MAX_TERMS 101
#define MAX_COL 50   /* max columns */
typedef struct {
  int row, col, value;   /* row, column, value */
} term;
term M[MAX_TERMS];

void transpose(term M[], term T[]) {
  int n = M[0].value, i, j, cur;
  T[0].row = M[0].col;  T[0].col = M[0].row;
  T[0].value = n;
  if (n > 0) {
    cur = 1;                       /* next in T */
    for (i = 0; i < M[0].col; i++)     /* each col */
      for (j = 1; j <= n; j++)         /* each term */
        if (M[j].col == i) {
          T[cur].row = M[j].col; T[cur].col = M[j].row;
          T[cur].value = M[j].value;  cur++;
        }
  }
}

/* not on the slides: prints a triple table */
static void print_terms(const char *name, const term t[]) {
  printf("%s: %dx%d, %d terms:", name, t[0].row, t[0].col, t[0].value);
  for (int i = 1; i <= t[0].value; i++)
    printf(" (%d,%d,%d)", t[i].row, t[i].col, t[i].value);
  printf("\n");
}

/* not on the slides: fills a triple table from a number array */
static void fill_terms(term t[], int rows, int cols, const int u[][3], int n) {
  t[0].row = rows; t[0].col = cols; t[0].value = n;
  for (int i = 0; i < n; i++) {
    t[i + 1].row = u[i][0]; t[i + 1].col = u[i][1]; t[i + 1].value = u[i][2];
  }
}

int main(void)
{
  static term T[MAX_TERMS];
  const int small[][3] = {{0, 0, 7}, {0, 3, 3}, {1, 1, 4}, {2, 0, 2}};
  const int large[][3] = {{0, 0, 15}, {0, 3, 22}, {0, 5, -15}, {1, 1, 11},
                          {1, 2, 3}, {2, 3, -6}, {4, 0, 91}, {5, 2, 28}};

  fill_terms(M, 3, 4, small, 4);
  print_terms("M", M);
  transpose(M, T);
  print_terms("T", T);

  fill_terms(M, 6, 6, large, 8);
  print_terms("M", M);
  transpose(M, T);
  print_terms("T", T);
  return 0;
}

/* Expected output:
 * M: 3x4, 4 terms: (0,0,7) (0,3,3) (1,1,4) (2,0,2)
 * T: 4x3, 4 terms: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * M: 6x6, 8 terms: (0,0,15) (0,3,22) (0,5,-15) (1,1,11) (1,2,3) (2,3,-6) (4,0,91) (5,2,28)
 * T: 6x6, 8 terms: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 */
