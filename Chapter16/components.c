/* A union-find application: counting connected components. The roots of
 * the two endpoints of every edge are found; if the roots differ, the sets
 * are merged and the counter decreases by one.
 * Example from the notes: 6 vertices, edges (0,1), (2,3), (1,4), (3,2);
 * the result is 3 ({0,1,4}, {2,3}, {5}), final array -3 0 -2 2 0 -1.
 * Slide: "Trace: components". */
#include <stdio.h>

#define N 10   /* not on the slides: the size from the "parent array" slide */
int parent[N];

/* not on the slides: weighted union from the "union2" slide */
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

/* not on the slides: find with path compression from the "find2" slide */
int find2(int i) {
  int r, s;
  for (r = i; parent[r] >= 0; r = parent[r])
    ;                   /* find the root */
  while (i != r) {      /* collapse the path */
    s = parent[i];      /* save i's parent */
    parent[i] = r;      /* link i directly to the root */
    i = s;              /* move up to the parent */
  }
  return r;
}

int components(int n, int m, int u[], int v[]) {
  for (int i = 0; i < n; i++) parent[i] = -1;
  int count = n;              /* every vertex separate */
  for (int e = 0; e < m; e++) {
    int a = find2(u[e]), b = find2(v[e]);
    if (a != b) {             /* a different component */
      union2(a, b);
      count--;
    }
  }
  return count;
}

int main(void)
{
    int u[] = {0, 2, 1, 3};
    int v[] = {1, 3, 4, 2};
    int i;
    printf("components(6, 4, u, v) = %d\n", components(6, 4, u, v));
    printf("parent =");
    for (i = 0; i < 6; i++) printf(" %d", parent[i]);
    printf("\n");
    return 0;
}

/* Expected output:
 * components(6, 4, u, v) = 3
 * parent = -3 0 -2 2 0 -1
 */
