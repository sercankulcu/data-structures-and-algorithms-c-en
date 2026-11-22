/* Depth-first search (DFS): recursive, O(n + e) with adjacency lists.
 * Example from the notes: a graph with 8 vertices and 10 edges, lists
 * sorted: 0:{1,2} 1:{0,3,4} 2:{0,5,6} 3:{1,7} 4:{1,7} 5:{2,7} 6:{2,7}
 * 7:{3,4,5,6}. dfs(0) = 0 1 3 7 4 5 2 6, dfs(7) = 7 3 1 0 2 5 6 4.
 * Slides: "DFS: Algorithm and Code", "DFS Step by Step" (and the following
 * ones). */
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

void dfs(int v)   /* depth-first search */
{
    node_ptr w;
    visited[v] = TRUE;    /* visited */
    printf("%d ", v);
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex);
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
void free_lists(node_ptr head[], int n)
{
    int i;
    node_ptr p;
    for (i = 0; i < n; i++) {
        while (head[i]) {
            p = head[i];
            head[i] = p->link;   /* save link before freeing */
            free(p);
        }
    }
}

int main(void)
{
    static const int k[10][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5},
        {2, 6}, {3, 7}, {4, 7}, {5, 7}, {6, 7}
    };
    int i;
    build_lists(k, 10);

    printf("dfs(0): ");
    dfs(0);
    printf("\n");

    for (i = 0; i < 8; i++) visited[i] = FALSE;   /* clear the marks */
    printf("dfs(7): ");
    dfs(7);
    printf("\n");

    free_lists(graph, 8);
    return 0;
}

/* Note: every number is followed by a space. */
/* Expected output:
 * dfs(0): 0 1 3 7 4 5 2 6
 * dfs(7): 7 3 1 0 2 5 6 4
 */
