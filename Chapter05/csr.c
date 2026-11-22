/* Compressed sparse row (CSR) representation and the matrix-vector product
 * y = M * x. val and col_ind hold the nonzero entries in row order; row i is
 * the range val[row_ptr[i] .. row_ptr[i+1]-1]. An empty row (row 3) shows up
 * as two equal row_ptr values.
 * Example from the notes: the 6 x 6 sample matrix and x = (1, 2, 3, 4, 5, 6).
 * Slide: "Compressed Sparse Row (CSR)". */
#include <stdio.h>

int main(void)
{
    /* not on the slides: CSR arrays of the 6 x 6 matrix in the notes */
    int val[]     = {15, 22, -15, 11, 3, -6, 91, 28};
    int col_ind[] = { 0,  3,   5,  1, 2,  3,  0,  2};
    int row_ptr[] = {0, 3, 5, 6, 6, 7, 8};
    int x[] = {1, 2, 3, 4, 5, 6};
    int y[6];
    int rows = 6, i, k;

    /* y = M * x  (matrix-vector product) */
    for (i = 0; i < rows; i++) {
      y[i] = 0;
      for (k = row_ptr[i]; k < row_ptr[i+1]; k++)
        y[i] += val[k] * x[col_ind[k]];
    }

    printf("y =");                          /* not on the slides */
    for (i = 0; i < rows; i++) printf(" %d", y[i]);
    printf("\n");
    return 0;
}

/* Expected output:
 * y = 13 31 -24 0 91 84
 */
