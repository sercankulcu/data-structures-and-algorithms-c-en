/* Topological sort (AOV network): headers with a count field hold the number
 * of predecessors; vertices whose count is 0 wait in a stack embedded in the
 * count field. If vertices remain unprinted when the stack runs empty, the
 * graph has a cycle.
 * Example from the notes: <0,1>, <0,2>, <0,3>, <1,4>, <2,4>, <2,5>, <3,5>,
 * <3,4> (lists are built in this order, appending at the end); output
 * 0 3 2 5 1 4.
 * Second example (not on the slides): the cycle 0->1, 1->2, 2->1; output
 * "0 cycle".
 * Slides: "Data Structure: A Predecessor Count in the Header", "The
 * Topological Sort Function", "Code Trace: ..." (two slides). */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 6   /* not on the slides: the chapter's constant */

typedef struct node *node_pointer;
typedef struct node {
    int vertex;
    node_pointer link;
} node;
typedef struct {
    int count;      /* for <i,j>: the number of edges whose head is j */
    node_pointer link;
} hdnodes;
hdnodes graph[MAX_VERTICES];

void topsort(hdnodes graph[], int n)
{
    int i, j, k, top = -1;
    node_pointer p;
    for (i = 0; i < n; i++)      /* count 0: push */
        if (!graph[i].count) {
            graph[i].count = top;  top = i; }
    for (i = 0; i < n; i++) {
        if (top == -1) { printf("cycle"); break; }
        j = top;  top = graph[top].count;
        printf("%d ", j);
        for (p = graph[j].link; p; p = p->link) {
            k = p->vertex;
            if (--graph[k].count == 0) {
                graph[k].count = top;  top = k; }
        }
    }
}

/* not on the slides: add_edge from the notes (appends, increments the count) */
int add_edge(hdnodes graph[], int i, int j)
{
    node_pointer *tail = &graph[i].link;   /* address of the link field */
    node_pointer new_node = malloc(sizeof(node));
    if (new_node == NULL)
        return 0;                     /* out of memory */
    new_node->vertex = j;
    new_node->link = NULL;
    while (*tail != NULL)             /* find the end of the list */
        tail = &(*tail)->link;
    *tail = new_node;
    graph[j].count++;                 /* j has one more predecessor */
    return 1;
}

/* not on the slides: free_lists from the notes */
void free_lists(hdnodes graph[], int n)
{
    int i;
    node_pointer p, next;
    for (i = 0; i < n; i++) {
        for (p = graph[i].link; p; p = next) {
            next = p->link;           /* save before free */
            free(p);
        }
        graph[i].link = NULL;
        graph[i].count = 0;
    }
}

int main(void)
{
    static const int net[8][2] = {
        {0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 4}, {2, 5}, {3, 5}, {3, 4}
    };
    static const int cyclic[3][2] = { {0, 1}, {1, 2}, {2, 1} };
    int i;

    for (i = 0; i < 8; i++)
        if (!add_edge(graph, net[i][0], net[i][1])) exit(1);
    topsort(graph, 6);
    printf("\n");
    free_lists(graph, 6);

    for (i = 0; i < 3; i++)
        if (!add_edge(graph, cyclic[i][0], cyclic[i][1])) exit(1);
    topsort(graph, 3);
    printf("\n");
    free_lists(graph, 3);
    return 0;
}

/* Note: there is a space after every number. */
/* Expected output:
 * 0 3 2 5 1 4 
 * 0 cycle
 */
