/* Adjacency list declaration and add_edge: every edge enters the front of a
 * list in O(1), so the lists are in the reverse of the arrival order.
 * Example from the notes: the edges of the triangle (0,1), (0,2), (1,2) are
 * added in this order.
 * Slides: "Adjacency Lists", "Building Lists Step by Step". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 50   /* max number of vertices */
typedef struct node *node_ptr;
typedef struct node {
    int vertex;        /* the neighbor's number */
    node_ptr link;     /* next neighbor in the list */
} node;                /* don't forget ';' and the typedef name */
node_ptr graph[MAX_V];   /* one list per vertex */

void add_edge(int u, int v)   /* u -> v */
{
    node_ptr p = malloc(sizeof(node));
    if (p == NULL) exit(1);       /* no memory */
    p->vertex = v;
    p->link = graph[u];   /* at the front: O(1) */
    graph[u] = p;
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

/* not on the slides: prints the lists */
static void print_lists(int n)
{
    int i;
    node_ptr p;
    for (i = 0; i < n; i++) {
        printf("graph[%d]:", i);
        for (p = graph[i]; p; p = p->link)
            printf(" %d", p->vertex);
        printf("\n");
    }
}

int main(void)
{
    /* every undirected edge is added with two calls */
    add_edge(0, 1);  add_edge(1, 0);
    add_edge(0, 2);  add_edge(2, 0);
    add_edge(1, 2);  add_edge(2, 1);
    print_lists(3);
    free_lists(graph, 3);
    return 0;
}

/* Expected output:
 * graph[0]: 2 1
 * graph[1]: 2 0
 * graph[2]: 1 0
 */
