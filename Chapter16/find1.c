/* Disjoint sets with a parent array, first version: find1 climbs to the
 * root, union1 links one root under the other with a single assignment.
 * 1) The forest in the notes: parent = {-1, 4, -1, 2, -1, 2, 0, 0, 0, 4};
 *    find1(9), union1(4, 0), find1(9) again.
 * 2) A bad sequence of operations (n = 5): union1(0,1) ... union1(3,4)
 *    builds a chain; find1(i) makes n - 1 - i steps, n(n-1)/2 in total.
 * Slides: "parent array", "find1 and union1",
 * "Trace: find1 / union1", "Trace: bad operation sequence", "Analysis". */
#include <stdio.h>

#define N 10
int parent[N] = { -1, 4, -1, 2, -1, 2, 0, 0, 0, 4 };

int find1(int i) {
  for (; parent[i] >= 0; i = parent[i])
    ;                /* climb until negative */
  return i;
}
void union1(int i, int j) {
  parent[i] = j;     /* link the set of i under j */
}

/* not on the slides: counts the distance to the root (number of steps) */
static int depth(int i)
{
    int d = 0;
    for (; parent[i] >= 0; i = parent[i])
        d++;
    return d;
}

/* not on the slides: prints the array */
static void print_parent(int n)
{
    int i;
    printf("parent =");
    for (i = 0; i < n; i++) printf(" %d", parent[i]);
    printf("\n");
}

int main(void)
{
    int i, n = 5, total = 0;

    printf("find1(9) = %d\n", find1(9));
    union1(4, 0);
    printf("after union1(4, 0) ");
    print_parent(N);
    printf("find1(9) = %d\n", find1(9));

    /* Analysis: start with n singleton sets */
    for (i = 0; i < n; i++) parent[i] = -1;
    for (i = 0; i < n - 1; i++)
        union1(i, i + 1);
    printf("chain: ");
    print_parent(n);
    for (i = 0; i < n; i++) {
        printf("find1(%d) = %d, steps = %d\n",
               i, find1(i), depth(i));
        total += depth(i);
    }
    printf("total steps = %d\n", total);
    return 0;
}

/* Expected output:
 * find1(9) = 4
 * after union1(4, 0) parent = -1 4 -1 2 0 2 0 0 0 4
 * find1(9) = 0
 * chain: parent = 1 2 3 4 -1
 * find1(0) = 4, steps = 4
 * find1(1) = 4, steps = 3
 * find1(2) = 4, steps = 2
 * find1(3) = 4, steps = 1
 * find1(4) = 4, steps = 0
 * total steps = 10
 */
