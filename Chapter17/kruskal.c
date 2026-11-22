/* Kruskal: edges are sorted by cost with qsort; an edge that creates no cycle
 * (its endpoints have different roots) joins the tree. The sets are kept with
 * weighted union and find.
 * Example from the notes: the seven-bay graph, 9 edges; the minimum spanning
 * tree costs 99 and the final parent array is 1 -7 1 2 1 0 1.
 * Slides: "C: Sets (Union-Find) and the Comparator", "Code Trace: ..."
 * (two slides). */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, w; } edge;

int find(int parent[], int i)   /* root: parent < 0 */
{
    while (parent[i] >= 0) i = parent[i];
    return i;
}
void unite(int parent[], int a, int b)   /* a, b are roots */
{
    if (parent[a] <= parent[b]) {   /* a is the larger set */
        parent[a] += parent[b];  parent[b] = a;
    } else {
        parent[b] += parent[a];  parent[a] = b;
    }
}
int cmp(const void *x, const void *y)
{
    return ((const edge *)x)->w - ((const edge *)y)->w;
}

int main(void)
{
    /* not on the slides: the example graph and variables */
    edge edges[] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int n = 7, e = 9, i, t, total = 0;
    int parent[7];
    edge T[6];

    for (i = 0; i < n; i++) parent[i] = -1;
    qsort(edges, e, sizeof(edge), cmp);
    for (i = 0, t = 0; i < e && t < n - 1; i++) {
        int a = find(parent, edges[i].u);
        int b = find(parent, edges[i].v);
        if (a != b) {                 /* no cycle */
            T[t++] = edges[i];
            unite(parent, a, b);
        }                             /* else skip */
    }
    if (t < n - 1) printf("no spanning tree\n");

    /* not on the slides: print the result */
    for (i = 0; i < t; i++) {
        printf("(%d,%d) %d\n", T[i].u, T[i].v, T[i].w);
        total += T[i].w;
    }
    printf("cost = %d\n", total);
    printf("parent =");
    for (i = 0; i < n; i++) printf(" %d", parent[i]);
    printf("\n");
    return 0;
}


/* Expected output:
 * (0,5) 10
 * (2,3) 12
 * (1,6) 14
 * (1,2) 16
 * (3,4) 22
 * (4,5) 25
 * cost = 99
 * parent = 1 -7 1 2 1 0 1
 */
