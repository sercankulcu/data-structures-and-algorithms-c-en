/* Floyd-Warshall: with intermediate vertex k in the outer loop,
 * A[i][j] = min(A[i][j], A[i][k] + A[k][j]); shortest paths between all
 * pairs, Theta(n^3).
 * Examples from the notes: Horowitz's three-vertex matrix (result 0 4 6 /
 * 5 0 2 / 3 7 0) and the chapter's main 6-vertex graph (row 0 is the same as
 * in Dijkstra).
 * Slide: "Code Trace: Floyd-Warshall" (function header from the notes). */
#include <stdio.h>

#define MAX_VERTICES 6   /* not on the slides: the chapter's constants */
#define INF 1000

/* not on the slides: function header from the notes */
void Floyd(int cost[][MAX_VERTICES], int A[][MAX_VERTICES], int n)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = cost[i][j];
    for (k = 0; k < n; k++)              /* via vertex k */
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
}

/* not on the slides: prints the matrix (oo instead of INF) */
static void print_matrix(int A[][MAX_VERTICES], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            if (A[i][j] >= INF) printf("   oo");
            else printf(" %4d", A[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int three[MAX_VERTICES][MAX_VERTICES] = {
        {0, 4, 11},
        {6, 0, 2},
        {3, INF, 0}
    };
    int six[MAX_VERTICES][MAX_VERTICES] = {
        {   0,   50,  10, 1000,   45, 1000},
        {1000,    0,  15, 1000,   10, 1000},
        {  20, 1000,   0,   15, 1000, 1000},
        {1000,   20, 1000,   0,   35, 1000},
        {1000, 1000, 1000,  30,    0, 1000},
        {1000, 1000, 1000,   3, 1000,    0}};
    int A[MAX_VERTICES][MAX_VERTICES];

    Floyd(three, A, 3);
    printf("three vertices:\n");
    print_matrix(A, 3);
    Floyd(six, A, 6);
    printf("six vertices:\n");
    print_matrix(A, 6);
    return 0;
}


/* Expected output:
 * three vertices:
 *     0    4    6
 *     5    0    2
 *     3    7    0
 * six vertices:
 *     0   45   10   25   45   oo
 *    35    0   15   30   10   oo
 *    20   35    0   15   45   oo
 *    55   20   35    0   30   oo
 *    85   50   65   30    0   oo
 *    58   23   38    3   33    0
 */
