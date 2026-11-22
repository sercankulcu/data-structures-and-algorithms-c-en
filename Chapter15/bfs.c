/* Breadth-first search (BFS) with a dynamic queue built from a linked list
 * (addq, deleteq). A vertex is marked when it is added to the queue.
 * Example from the notes: the same 8-vertex graph as for DFS, lists sorted.
 * bfs(0) = 0 1 2 3 4 5 6 7, bfs(7) = 7 3 4 5 6 1 2 0.
 * Slides: "BFS: Algorithm", "BFS: Dynamic Queue", "BFS Step by Step"
 * (and the following ones). */
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

typedef struct queue *queue_ptr;
typedef struct queue {
    int vertex;
    queue_ptr link;
} queue;
void addq(queue_ptr *f,
          queue_ptr *r, int d)
{
    queue_ptr p = malloc(sizeof(queue));
    if (p == NULL) exit(1);
    p->vertex = d;  p->link = NULL;
    if (*f) (*r)->link = p;  else *f = p;
    *r = p;
}

int deleteq(queue_ptr *f,
            queue_ptr *r)
{
    queue_ptr p = *f;   /* f != NULL */
    int d = p->vertex;
    *f = p->link;
    if (*f == NULL) *r = NULL;
    free(p);
    return d;
}

void bfs(int v)   /* breadth-first search */
{
    node_ptr w;
    queue_ptr front = NULL, rear = NULL;
    printf("%d ", v);
    visited[v] = TRUE;
    addq(&front, &rear, v);
    while (front) {
        v = deleteq(&front, &rear);
        for (w = graph[v]; w; w = w->link)
            if (!visited[w->vertex]) {
                printf("%d ", w->vertex);
                addq(&front, &rear, w->vertex);
                visited[w->vertex] = TRUE;
            }
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
    static const int k[10][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5},
        {2, 6}, {3, 7}, {4, 7}, {5, 7}, {6, 7}
    };
    int i;
    build_lists(k, 10);

    printf("bfs(0): ");
    bfs(0);
    printf("\n");

    for (i = 0; i < 8; i++) visited[i] = FALSE;   /* clear the marks */
    printf("bfs(7): ");
    bfs(7);
    printf("\n");

    free_lists(graph, 8);
    return 0;
}

/* Note: every number is followed by a space. */
/* Expected output:
 * bfs(0): 0 1 2 3 4 5 6 7
 * bfs(7): 7 3 4 5 6 1 2 0
 */
