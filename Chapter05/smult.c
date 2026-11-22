/* Sparse matrix multiplication D = A * B in the triple representation. First
 * the transpose of B (bt) is taken, so the columns of B become consecutive rows.
 * row_end() finds where a row ends, dot() merges two rows by column field to
 * compute their dot product, store() writes a nonzero sum into the result.
 * Examples from the notes: A = [[1,0,2],[0,3,0]], B = [[4,0],[0,5],[6,0]] and
 * two 3 x 3 sparse matrices whose product is full.
 * Slides: "Helpers: End of Row, dot Product, store", "Sparse Multiplication:
 * Row of A . Row of B^T". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: definitions from the "A Sparse Matrix" slide */
#define MAX_TERMS 101
#define MAX_COL 50   /* max columns */
typedef struct {
  int row, col, value;   /* row, column, value */
} term;

/* where the row of the term at s ends */
int row_end(term t[], int s) {
  int e = s;
  while (e <= t[0].value &&
         t[e].row == t[s].row) e++;
  return e;
}
/* dot product of row a[x..ex) and row b[y..ey) */
int dot(term a[], int x, int ex,
         term b[], int y, int ey) {
  int sum = 0;
  while (x < ex && y < ey)
    if (a[x].col < b[y].col) x++;
    else if (a[x].col > b[y].col) y++;
    else sum += a[x++].value * b[y++].value;
  return sum;
}

void store(term d[], int *nd,
      int r, int c, int s) {
  if (s == 0) return;
  if (++*nd >= MAX_TERMS) {
    fprintf(stderr, "Too many terms\n");
    exit(1);
  }
  d[*nd].row = r;
  d[*nd].col = c;
  d[*nd].value = s;
}

void smult(term a[], term bt[], term d[]) {
  int ra, ea, rb, eb, nd = 0;
  for (ra = 1; ra <= a[0].value; ra = ea) {
    ea = row_end(a, ra);           /* row of A [ra,ea) */
    for (rb = 1; rb <= bt[0].value; rb = eb) {
      eb = row_end(bt, rb);        /* col of B [rb,eb) */
      store(d, &nd, a[ra].row, bt[rb].row,
            dot(a, ra, ea, bt, rb, eb));
    }
  }
  d[0].row = a[0].row;  d[0].col = bt[0].row;
  d[0].value = nd;
}

/* not on the slides: fast_transpose from its slide, used to build bt */
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
  static term a[MAX_TERMS], b[MAX_TERMS], bt[MAX_TERMS], d[MAX_TERMS];
  const int a1[][3] = {{0, 0, 1}, {0, 2, 2}, {1, 1, 3}};
  const int b1[][3] = {{0, 0, 4}, {1, 1, 5}, {2, 0, 6}};
  const int a2[][3] = {{0, 0, 1}, {1, 0, 1}, {2, 0, 1}};
  const int b2[][3] = {{0, 0, 1}, {0, 1, 1}, {0, 2, 1}};

  fill_terms(a, 2, 3, a1, 3);
  fill_terms(b, 3, 2, b1, 3);
  fast_transpose(b, bt);
  print_terms("a", a);
  print_terms("bt", bt);
  smult(a, bt, d);
  print_terms("d", d);

  fill_terms(a, 3, 3, a2, 3);
  fill_terms(b, 3, 3, b2, 3);
  fast_transpose(b, bt);
  print_terms("a", a);
  print_terms("bt", bt);
  smult(a, bt, d);
  print_terms("d", d);
  return 0;
}

/* Expected output:
 * a: 2x3, 3 terms: (0,0,1) (0,2,2) (1,1,3)
 * bt: 2x3, 3 terms: (0,0,4) (0,2,6) (1,1,5)
 * d: 2x2, 2 terms: (0,0,16) (1,1,15)
 * a: 3x3, 3 terms: (0,0,1) (1,0,1) (2,0,1)
 * bt: 3x3, 3 terms: (0,0,1) (1,0,1) (2,0,1)
 * d: 3x3, 9 terms: (0,0,1) (0,1,1) (0,2,1) (1,0,1) (1,1,1) (1,2,1) (2,0,1) (2,1,1) (2,2,1)
 */
