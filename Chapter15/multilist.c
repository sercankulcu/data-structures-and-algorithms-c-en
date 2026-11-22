/* Adjacency multilist: every edge of an undirected graph is a single node
 * that appears in the lists of both of its endpoints. ml_add_edge puts the
 * edge at the front of both lists; print_adj tests which endpoint v is and
 * follows the right link.
 * Example from the notes: the edges of G1, (0,1), (0,2), (0,3), (1,2),
 * (1,3), (2,3), are added in this order with ml_add_edge; print_adj(2)
 * prints "3 1 0".
 * Slides: "Multilist", "Traversing a Multilist", "Adding to a Multilist". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 50   /* not on the slides: the constant from the "Adjacency Lists" slide */

typedef struct edge *edge_ptr;
typedef struct edge {
    short marked;        /* processed? */
    int vertex1, vertex2;  /* the endpoints */
    edge_ptr list1;      /* next edge for vertex1 */
    edge_ptr list2;      /* next edge for vertex2 */
} edge;
edge_ptr graph[MAX_V];

void print_adj(int v)
{
    edge_ptr p = graph[v];
    while (p) {
        if (p->vertex1 == v) {      /* v: vertex1 */
            printf("%d ", p->vertex2);  p = p->list1;
        } else {                    /* v: vertex2 */
            printf("%d ", p->vertex1);  p = p->list2;
        }
    }
}

void ml_add_edge(int u, int v)
{
    edge_ptr p = malloc(sizeof(edge));
    if (p == NULL) exit(1);
    p->marked = 0;
    p->vertex1 = u;  p->vertex2 = v;
    p->list1 = graph[u];  /* u's list */
    p->list2 = graph[v];  /* v's list */
    graph[u] = graph[v] = p;  /* front of both */
}

/* not on the slides: since every edge is in two lists, it is collected once,
 * from the vertex1 side, and then all of them are freed */
static void free_edges(int n)
{
    edge_ptr all[64];
    int count = 0, v, i;
    edge_ptr p;
    for (v = 0; v < n; v++) {
        p = graph[v];
        while (p) {
            if (p->vertex1 == v) {
                all[count++] = p;  p = p->list1;
            } else {
                p = p->list2;
            }
        }
    }
    for (i = 0; i < count; i++) free(all[i]);
    for (v = 0; v < n; v++) graph[v] = NULL;
}

int main(void)
{
    int v;
    ml_add_edge(0, 1);  ml_add_edge(0, 2);  ml_add_edge(0, 3);
    ml_add_edge(1, 2);  ml_add_edge(1, 3);  ml_add_edge(2, 3);
    for (v = 0; v < 4; v++) {
        printf("print_adj(%d): ", v);
        print_adj(v);
        printf("\n");
    }
    free_edges(4);
    return 0;
}

/* Note: every number is followed by a space. */
/* Expected output:
 * print_adj(0): 3 2 1
 * print_adj(1): 3 2 0
 * print_adj(2): 3 1 0
 * print_adj(3): 2 1 0
 */
