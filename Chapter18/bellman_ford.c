/* Bellman-Ford: all E are relaxed n - 1 times; if an edge still relaxes
 * in round n, a reachable negative cycle exists (-1). O(n e).
 * Examples from the notes: 0->1 (4), 0->2 (5), 1->3 (2), 2->1 (-3):
 * d = 0 2 5 4; on the cycle 1 -> 2 -> 1 of total -1 the result is -1.
 * Slide: "Code Trace: Bellman-Ford (Source 0)" (function header from the
 * notes). */
#include <stdio.h>

#define INF 1000         /* not on the slides: the "no edge" constant */

/* not on the slides: edge list and function header from the notes */
typedef struct {
    int u, v, w;        /* edge <u,v>, weight w */
} edge;
int BellmanFord(edge E[], int n, int e, int s, int d[])
{
    int i, j, t, u, v;
    for (i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    for (t = 1; t <= n - 1; t++)          /* n-1 rounds */
        for (j = 0; j < e; j++) {
            u = E[j].u;  v = E[j].v;
            if (d[u] != INF && d[u] + E[j].w < d[v])
                d[v] = d[u] + E[j].w;
        }
    for (j = 0; j < e; j++)               /* round n */
        if (d[E[j].u] != INF &&
            d[E[j].u] + E[j].w < d[E[j].v]) return -1;
    return 0;              /* -1: negative cycle */
}

int main(void)
{
    edge E1[] = { {0, 1, 4}, {0, 2, 5}, {1, 3, 2}, {2, 1, -3} };
    edge E2[] = { {0, 1, 1}, {1, 2, 2}, {2, 1, -3} };
    int d[4], i, r;

    r = BellmanFord(E1, 4, 4, 0, d);
    printf("example: result = %d, d =", r);
    for (i = 0; i < 4; i++) printf(" %d", d[i]);
    printf("\n");

    r = BellmanFord(E2, 3, 3, 0, d);
    printf("negative cycle: result = %d\n", r);
    return 0;
}


/* Expected output:
 * example: result = 0, d = 0 2 5 4
 * negative cycle: result = -1
 */
