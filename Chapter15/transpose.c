/* Transpose (reverse) adjacency lists: every edge <i,j> is added to the list
 * rev[j] as i. Example from the notes: G3, adj[0] = 1, adj[1] = 0 -> 2,
 * adj[2] = NULL.
 * Slide: "Transpose List Step by Step". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 50   /* max number of vertices */
typedef struct node *node_ptr;
typedef struct node {
    int vertex;        /* the neighbor's number */
    node_ptr link;     /* next neighbor in the list */
} node;                /* don't forget ';' and the typedef name */
node_ptr graph[MAX_V];   /* one list per vertex */

/* not on the slides: insert from the notes (add_edge working on any array
 * of list heads) */
void insert(node_ptr adj[], int u, int v)   /* v into the list adj[u] */
{
    node_ptr p = malloc(sizeof(node));
    if (p == NULL) exit(1);
    p->vertex = v;
    p->link = adj[u];
    adj[u] = p;
}

void transpose(node_ptr adj[], node_ptr rev[],
               int n)
{
    int i;
    node_ptr p;
    for (i = 0; i < n; i++) rev[i] = NULL;
    for (i = 0; i < n; i++)
        for (p = adj[i]; p; p = p->link)
            insert(rev, p->vertex, i);  /* <j,i> */
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
static void print_lists(const char *name, node_ptr adj[], int n)
{
    int i;
    node_ptr p;
    for (i = 0; i < n; i++) {
        printf("%s[%d]:", name, i);
        for (p = adj[i]; p; p = p->link)
            printf(" %d", p->vertex);
        printf("\n");
    }
}

int main(void)
{
    node_ptr rev[MAX_V];
    /* G3: <0,1>, <1,0>, <1,2>; added at the front, so the list of 1 is 0 -> 2 */
    insert(graph, 0, 1);
    insert(graph, 1, 2);
    insert(graph, 1, 0);
    transpose(graph, rev, 3);
    print_lists("adj", graph, 3);
    print_lists("rev", rev, 3);
    free_lists(graph, 3);
    free_lists(rev, 3);
    return 0;
}

/* Expected output:
 * adj[0]: 1
 * adj[1]: 0 2
 * adj[2]:
 * rev[0]: 1
 * rev[1]: 0
 * rev[2]: 1
 */
