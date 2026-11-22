/* The collapsing rule (path compression, find2): the root is found first,
 * then every node on the path is linked directly to the root.
 * Example from the notes: the tree at the end of the weighted trace,
 * parent = {-8, 0, 0, 2, 0, 4, 4, 6}; find2(7), find2(7), find2(5) in
 * this order.
 * Slides: "find2", "Trace: find2(7)", "Trace: find2 (continued)". */
#include <stdio.h>

#define N 10   /* not on the slides: the size from the "parent array" slide */
int parent[N] = { -8, 0, 0, 2, 0, 4, 4, 6 };   /* not on the slides: the example tree */

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

/* not on the slides: prints the first 8 cells */
static void print_parent(void)
{
    int i;
    printf("  parent =");
    for (i = 0; i < 8; i++) printf(" %d", parent[i]);
    printf("\n");
}

int main(void)
{
    printf("find2(7) = %d\n", find2(7));
    print_parent();
    printf("find2(7) = %d\n", find2(7));
    print_parent();
    printf("find2(5) = %d\n", find2(5));
    print_parent();
    return 0;
}

/* Expected output:
 * find2(7) = 0
 *   parent = -8 0 0 2 0 4 0 0
 * find2(7) = 0
 *   parent = -8 0 0 2 0 4 0 0
 * find2(5) = 0
 *   parent = -8 0 0 2 0 0 0 0
 */
