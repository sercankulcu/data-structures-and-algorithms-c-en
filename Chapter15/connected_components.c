/* Connected components: a new dfs is started from every unmarked vertex;
 * each component is printed on its own line. Total work is O(n + e) (a
 * sum, not a product).
 * Example from the slide: 10 vertices, edges (0,1) (0,2) (1,3) (2,3) (4,5)
 * (4,6) (7,8) (8,9); output 0 1 3 2 / 4 5 6 / 7 8 9.
 * Slides: "Connected Components", "Components Step by Step". */
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

void connected(int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (!visited[i]) {   /* new */
            dfs(i);
            printf("\n");
        }
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
    static const int k[8][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3},
        {4, 5}, {4, 6}, {7, 8}, {8, 9}
    };
    build_lists(k, 8);
    connected(10);
    free_lists(graph, 10);
    return 0;
}

/* Note: every number is followed by a space. */
/* Expected output:
 * 0 1 3 2
 * 4 5 6
 * 7 8 9
 */
