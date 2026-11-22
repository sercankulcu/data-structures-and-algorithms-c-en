/* Prim with arrays, O(n^2): lowcost[v] is the cost of the cheapest edge that
 * connects v to the tree, closest[v] is the endpoint of that edge in the
 * tree. The graph is stored as a cost matrix (INF where there is no edge).
 * Example from the notes: the seven-bay graph, from 0; the vertices enter the
 * tree in the order 5, 4, 3, 2, 1, 6, total 99.
 * Slide: "Code Trace: ..." (Prim). */
#include <stdio.h>

#define INF 1000000      /* not on the slides: the constant from the notes */
#define N 7              /* not on the slides: number of vertices */

/* not on the slides: cheapest from the notes (linear search) */
int cheapest(const int lowcost[], const int in_tree[], int n)
{
    int v, u = -1;
    for (v = 0; v < n; v++)
        if (!in_tree[v] && lowcost[v] < INF &&
            (u < 0 || lowcost[v] < lowcost[u]))
            u = v;
    return u;            /* -1: no vertex is connected to TV */
}

int main(void)
{
    /* not on the slides: the example graph and variables */
    static const int edges[9][3] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int w[N][N], lowcost[N], closest[N], in_tree[N] = {0};
    int n = N, k, u, v, total = 0;
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            w[u][v] = (u == v) ? 0 : INF;
    for (k = 0; k < 9; k++) {
        w[edges[k][0]][edges[k][1]] = edges[k][2];
        w[edges[k][1]][edges[k][0]] = edges[k][2];
    }

    in_tree[0] = 1;                    /* TV = {0} */
    for (v = 0; v < n; v++)
        lowcost[v] = w[0][v], closest[v] = 0;
    for (k = 1; k < n; k++) {
        u = cheapest(lowcost, in_tree, n);  /* O(n) */
        if (u < 0) break;                   /* no tree */
        in_tree[u] = 1;  total += lowcost[u];
        printf("k=%d: (%d,%d) %d, total = %d\n",   /* not on the slides */
               k, closest[u], u, lowcost[u], total);
        for (v = 0; v < n; v++)
            if (!in_tree[v] && w[u][v] < lowcost[v])
                lowcost[v] = w[u][v], closest[v] = u;
    }

    /* not on the slides: the final arrays */
    printf("lowcost =");
    for (v = 0; v < n; v++) printf(" %d", lowcost[v]);
    printf("\nclosest =");
    for (v = 0; v < n; v++) printf(" %d", closest[v]);
    printf("\n");
    return 0;
}


/* Expected output:
 * k=1: (0,5) 10, total = 10
 * k=2: (5,4) 25, total = 35
 * k=3: (4,3) 22, total = 57
 * k=4: (3,2) 12, total = 69
 * k=5: (2,1) 16, total = 85
 * k=6: (1,6) 14, total = 99
 * lowcost = 0 16 12 22 25 10 14
 * closest = 0 2 3 4 5 0 1
 */
