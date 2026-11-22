/* The weighted union rule (union2): the root holds -(number of nodes), and
 * the tree with fewer nodes is linked under the one with more; the tree
 * height is at most floor(lg n) + 1.
 * Example from the notes: 8 singleton sets; union2(0,1), (2,3), (4,5),
 * (6,7), (0,2), (4,6), (0,4).
 * Slides: "union2", "Trace: union2 - 1", "Trace: union2 - 2". */
#include <stdio.h>

#define N 10   /* not on the slides: the size from the "parent array" slide */
int parent[N];

void union2(int i, int j) {
  /* weighting rule; i and j must be roots */
  int p = parent[i] + parent[j];  /* -(total nodes) */
  if (parent[i] > parent[j]) {    /* i has fewer nodes */
    parent[i] = j;                /* link i under j */
    parent[j] = p;                /* update j's count */
  } else {                        /* j has fewer or equal */
    parent[j] = i;
    parent[i] = p;
  }
}

int main(void)
{
    static const int pairs[7][2] = {
        {0, 1}, {2, 3}, {4, 5}, {6, 7}, {0, 2}, {4, 6}, {0, 4}
    };
    int i, c, n = 8;
    for (i = 0; i < n; i++) parent[i] = -1;
    for (c = 0; c < 7; c++) {
        union2(pairs[c][0], pairs[c][1]);
        printf("union2(%d, %d): parent =", pairs[c][0], pairs[c][1]);
        for (i = 0; i < n; i++) printf(" %d", parent[i]);
        printf("\n");
    }
    return 0;
}

/* Expected output:
 * union2(0, 1): parent = -2 0 -1 -1 -1 -1 -1 -1
 * union2(2, 3): parent = -2 0 -2 2 -1 -1 -1 -1
 * union2(4, 5): parent = -2 0 -2 2 -2 4 -1 -1
 * union2(6, 7): parent = -2 0 -2 2 -2 4 -2 6
 * union2(0, 2): parent = -4 0 0 2 -2 4 -2 6
 * union2(4, 6): parent = -4 0 0 2 -4 4 4 6
 * union2(0, 4): parent = -8 0 0 2 0 4 4 6
 */
