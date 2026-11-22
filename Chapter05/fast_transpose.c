/* Fast transpose: phase 1 finds the number of terms in each column
 * (row_terms) and their starting position in the transpose (start_pos, prefix
 * sums); phase 2 scans M once and writes every triple directly into place. The
 * second function is the one-array version from the analysis slide: the count
 * array is turned into start positions in place.
 * Examples from the notes: a 3 x 4 matrix and a 6 x 6 matrix.
 * Slides: "fast_transpose (1): Count and Find the Starts", "fast_transpose (2):
 * Put the Terms in Place", "Analysis, and a Version with One Array". */
#include <stdio.h>

/* not on the slides: definitions from the "A Sparse Matrix" slide */
#define MAX_TERMS 101
#define MAX_COL 50   /* max columns */
typedef struct {
  int row, col, value;   /* row, column, value */
} term;

void fast_transpose(term M[], term T[]) {
  int i, j, nc = M[0].col, nt = M[0].value;
  int row_terms[MAX_COL], start_pos[MAX_COL];
  T[0].row = nc;  T[0].col = M[0].row;  T[0].value = nt;
  if (nt <= 0) return;                    /* empty matrix */
  for (i = 0; i < nc; i++) row_terms[i] = 0;
  for (i = 1; i <= nt; i++) row_terms[M[i].col]++;
  start_pos[0] = 1;
  for (i = 1; i < nc; i++)
    start_pos[i] = start_pos[i-1] + row_terms[i-1];
  for (i = 1; i <= nt; i++) {
    j = start_pos[M[i].col]++;       /* take slot, bump */
    T[j].row = M[i].col;  T[j].col = M[i].row;
    T[j].value = M[i].value;
  }
}

/* not on the slides: function header, header triple and counting; the part
 * shown on the slide is marked below */
void fast_transpose_one_array(term M[], term T[]) {
  int i, j, pos, nc = M[0].col, nt = M[0].value;
  int row_terms[MAX_COL];
  T[0].row = nc;  T[0].col = M[0].row;  T[0].value = nt;
  if (nt <= 0) return;
  for (i = 0; i < nc; i++) row_terms[i] = 0;
  for (i = 1; i <= nt; i++) row_terms[M[i].col]++;
  /* --- the part on the slide --- */
  /* turn row_terms into start_pos in place */
  for (i = 0, pos = 1; i < nc; i++) {
    int c = row_terms[i];  /* terms in this column */
    row_terms[i] = pos;  /* now a start position */
    pos += c;
  }
  for (i = 1; i <= nt; i++) {
    j = row_terms[M[i].col]++;
    T[j].row = M[i].col;  T[j].col = M[i].row;
    T[j].value = M[i].value;
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
  static term M[MAX_TERMS], T[MAX_TERMS], T2[MAX_TERMS];
  const int small[][3] = {{0, 0, 7}, {0, 3, 3}, {1, 1, 4}, {2, 0, 2}};
  const int large[][3] = {{0, 0, 15}, {0, 3, 22}, {0, 5, -15}, {1, 1, 11},
                          {1, 2, 3}, {2, 3, -6}, {4, 0, 91}, {5, 2, 28}};

  fill_terms(M, 3, 4, small, 4);
  print_terms("M", M);
  fast_transpose(M, T);
  print_terms("T", T);
  fast_transpose_one_array(M, T2);
  print_terms("T (one array)", T2);

  fill_terms(M, 6, 6, large, 8);
  print_terms("M", M);
  fast_transpose(M, T);
  print_terms("T", T);
  fast_transpose_one_array(M, T2);
  print_terms("T (one array)", T2);
  return 0;
}

/* Expected output:
 * M: 3x4, 4 terms: (0,0,7) (0,3,3) (1,1,4) (2,0,2)
 * T: 4x3, 4 terms: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * T (one array): 4x3, 4 terms: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * M: 6x6, 8 terms: (0,0,15) (0,3,22) (0,5,-15) (1,1,11) (1,2,3) (2,3,-6) (4,0,91) (5,2,28)
 * T: 6x6, 8 terms: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 * T (one array): 6x6, 8 terms: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 */
