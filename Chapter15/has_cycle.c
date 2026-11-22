/* Cycle detection in an undirected graph: if DFS meets a marked neighbor
 * other than the parent, that is a back edge, so there is a cycle.
 * Examples from the notes: in the graph with edges 0-1, 1-2, 2-3, 3-1,
 * has_cycle(0, -1) is TRUE (back edge (3,1)); in the tree G2 it is FALSE.
 * Slide: "Cycle Detection". */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */
#define TRUE  true
#define FALSE false

#define MAX_V 50   /* max number of vertices */
typedef struct node *node_ptr;
typedef struct node {
    int vertex;        /* the neighbor's number */
    node_ptr link;     /* next neighbor in the list */
} node;                /* don't forget ';' and the typedef name */
node_ptr graph[MAX_V];   /* one list per vertex */

bool visited[MAX_V];   /* don't forget ';' */

bool has_cycle(int v, int parent)
{
    node_ptr w;
    visited[v] = TRUE;
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex]) {
            if (has_cycle(w->vertex, v)) return TRUE;
        } else if (w->vertex != parent)
            return TRUE;          /* back edge */
    return FALSE;
}

/* not on the slides: add_edge from the "Building Lists" slide */
void add_edge(int u, int v)   /* u -> v */
{
    node_ptr p = malloc(sizeof(node));
    if (p == NULL) exit(1);       /* no memory */
    p->vertex = v;
    p->link = graph[u];   /* at the front: O(1) */
    graph[u] = p;
}

/* not on the slides: adds undirected edges at the front in reverse order,
 * so that every list ends up in ascending order */
static void build_lists(const int k[][2], int e)
{
    int i;
    for (i = e - 1; i >= 0; i--) {
        add_edge(k[i][0], k[i][1]);
        add_edge(k[i][1], k[i][0]);
    }
}

/* not on the slides: free_lists from the notes */
void free_lists(node_ptr adj[], int n)
{
    int i;
    node_ptr p;
    for (i = 0; i < n; i++) {
        while (adj[i]) {
            p = adj[i];
            adj[i] = p->link;   /* save link before freeing */
            free(p);
        }
    }
}

int main(void)
{
    static const int cyclic[4][2] = { {0, 1}, {1, 2}, {1, 3}, {2, 3} };
    static const int g2[6][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}
    };
    int i;

    build_lists(cyclic, 4);
    printf("0-1, 1-2, 2-3, 3-1: has_cycle(0, -1) = %d\n", has_cycle(0, -1));
    free_lists(graph, 4);

    for (i = 0; i < MAX_V; i++) visited[i] = FALSE;   /* clear the marks */
    build_lists(g2, 6);
    printf("G2 (tree): has_cycle(0, -1) = %d\n", has_cycle(0, -1));
    free_lists(graph, 7);
    return 0;
}

/* Expected output:
 * 0-1, 1-2, 2-3, 3-1: has_cycle(0, -1) = 1
 * G2 (tree): has_cycle(0, -1) = 0
 */
