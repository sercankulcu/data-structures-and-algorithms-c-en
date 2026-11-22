/* Degree in a directed graph with an adjacency matrix: the row sum is the
 * out-degree, the column sum the in-degree. Example from the notes: G3
 * (<0,1>, <1,0>, <1,2>); degree(a, 3, 1) = 2 + 1 = 3.
 * Slide: "Degree in a Matrix Step by Step". */
#include <stdio.h>

#define MAX_V 50   /* not on the slides: the constant from the "Adjacency Lists" slide */

int degree(int a[][MAX_V], int n, int v)
{
    int j, out = 0, in = 0;
    for (j = 0; j < n; j++)
        out += a[v][j];      /* row    */
    for (j = 0; j < n; j++)
        in += a[j][v];       /* column */
    return out + in;
}

/* not on the slides: the adjacency matrix of G3 (remaining cells are 0) */
static int a[MAX_V][MAX_V] = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 0, 0}
};

int main(void)
{
    int v;
    for (v = 0; v < 3; v++)
        printf("degree(a, 3, %d) = %d\n", v, degree(a, 3, v));
    return 0;
}

/* Expected output:
 * degree(a, 3, 0) = 2
 * degree(a, 3, 1) = 3
 * degree(a, 3, 2) = 1
 */
