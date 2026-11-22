/* Two representations of a weighted graph: a cost matrix (INF where there
 * is no edge, 0 on the diagonal) and adjacency lists with a weight field in
 * every node.
 * Example from the notes: A-B 4, A-C 2, B-C 1, B-D 5, C-D 8 (A=0, B=1,
 * C=2, D=3).
 * Slide: "Weighted Graph Representation". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 50   /* not on the slides: the constant from the "Adjacency Lists" slide */

#define INF 1000000   /* not INT_MAX: sums overflow */
int cost[MAX_V][MAX_V];

typedef struct wnode *wnode_ptr;
typedef struct wnode {
    int vertex;
    int weight;        /* cost of the edge */
    wnode_ptr link;
} wnode;
wnode_ptr wgraph[MAX_V];

/* not on the slides: puts (v, w) at the front of the list wgraph[u] */
static void add_wedge(int u, int v, int w)
{
    wnode_ptr p = malloc(sizeof(wnode));
    if (p == NULL) exit(1);
    p->vertex = v;
    p->weight = w;
    p->link = wgraph[u];
    wgraph[u] = p;
}

/* not on the slides: frees the lists */
static void free_wlists(int n)
{
    int i;
    wnode_ptr p;
    for (i = 0; i < n; i++)
        while (wgraph[i]) {
            p = wgraph[i];
            wgraph[i] = p->link;
            free(p);
        }
}

int main(void)
{
    const char *name = "ABCD";
    int n = 4, i, j;
    wnode_ptr p;

    /* not on the slides: fill the matrix */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            cost[i][j] = (i == j) ? 0 : INF;
    cost[0][1] = cost[1][0] = 4;
    cost[0][2] = cost[2][0] = 2;
    cost[1][2] = cost[2][1] = 1;
    cost[1][3] = cost[3][1] = 5;
    cost[2][3] = cost[3][2] = 8;

    /* build the lists from the matrix; adding with j decreasing makes the
       lists come out in ascending order */
    for (i = 0; i < n; i++)
        for (j = n - 1; j >= 0; j--)
            if (i != j && cost[i][j] != INF)
                add_wedge(i, j, cost[i][j]);

    printf("cost matrix:\n");
    for (i = 0; i < n; i++) {
        printf("%c:", name[i]);
        for (j = 0; j < n; j++)
            if (cost[i][j] == INF) printf(" oo");
            else printf(" %d", cost[i][j]);
        printf("\n");
    }
    printf("adjacency lists (neighbor/weight):\n");
    for (i = 0; i < n; i++) {
        printf("%c:", name[i]);
        for (p = wgraph[i]; p; p = p->link)
            printf(" %c/%d", name[p->vertex], p->weight);
        printf("\n");
    }
    free_wlists(n);
    return 0;
}

/* Expected output:
 * cost matrix:
 * A: 0 4 2 oo
 * B: 4 0 1 5
 * C: 2 1 0 8
 * D: oo 5 8 0
 * adjacency lists (neighbor/weight):
 * A: B/4 C/2
 * B: A/4 C/1 D/5
 * C: A/2 B/1 D/8
 * D: B/5 C/8
 */
