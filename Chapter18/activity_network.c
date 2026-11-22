/* Activity-on-edge (AoE) network: the forward pass in topological order finds
 * the earliest event times (largest), the backward pass on the reversed graph
 * finds the latest times (smallest); activities with slack 0 are critical.
 * Example from the notes: 9 events, 11 activities (a0..a10); the project
 * takes 18 days, earliest = 0 6 4 5 7 7 16 14 18, latest = 0 6 6 8 7 10 16 14
 * 18, critical activities a0, a3, a6, a7, a9, a10.
 * Slides: "Earliest Start Times", "Code Trace: earliest[] (in Topological
 * Order)" (and its continuation), "Latest Start Times", "Code Trace: latest[]
 * (on the Reversed Graph)", "Let the Program Find the Critical Path (Extra
 * Topic)". Function names are from the notes. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10   /* not on the slides: for 9 events (6 is too few) */

/* not on the slides: list node with a duration field and the counted header
 * from the notes */
typedef struct node *node_pointer;
typedef struct node {
    int vertex;
    int duration;        /* duration of the activity */
    node_pointer link;
} node;
typedef struct {
    int count;
    node_pointer link;
} hdnodes;
int earliest[MAX_VERTICES], latest[MAX_VERTICES];

/* not on the slides: add_edge from the notes (appends, increments the count) */
int add_edge(hdnodes graph[], int i, int j, int duration)
{
    node_pointer *last = &graph[i].link;
    node_pointer fresh = malloc(sizeof(node));
    if (fresh == NULL)
        return 0;
    fresh->vertex = j;
    fresh->duration = duration;
    fresh->link = NULL;
    while (*last != NULL)
        last = &(*last)->link;
    *last = fresh;
    graph[j].count++;
    return 1;
}

/* forward pass: topsort + the earliest-time lines */
void compute_earliest(hdnodes graph[], int n)
{
    int i, j, k, top = -1;
    node_pointer p;
    for (i = 0; i < n; i++)
        earliest[i] = 0;
    for (i = 0; i < n; i++)
        if (!graph[i].count) {
            graph[i].count = top;  top = i; }
    for (i = 0; i < n; i++) {
        if (top == -1) { printf("cycle"); break; }
        j = top;  top = graph[top].count;   /* pop */
        printf("%d ", j);
        for (p = graph[j].link; p; p = p->link) {
            k = p->vertex;
            if (earliest[k] < earliest[j] + p->duration)
                earliest[k] = earliest[j] + p->duration;
            if (--graph[k].count == 0) {
                graph[k].count = top;  top = k;  /* push */
            }
        }
    }
}

/* not on the slides: reverse_graph from the notes (reverses the arrows) */
int reverse_graph(hdnodes graph[], hdnodes rev[], int n)
{
    int i;
    node_pointer p;
    for (i = 0; i < n; i++) {
        rev[i].count = 0;
        rev[i].link = NULL;
    }
    for (i = 0; i < n; i++)
        for (p = graph[i].link; p; p = p->link)      /* <i, p->vertex> */
            if (!add_edge(rev, p->vertex, i, p->duration))
                return 0;
    return 1;
}

/* backward pass: the same loop on the reversed graph, latest-time lines */
void compute_latest(hdnodes graph[], int n, int project)
{
    int i, j, k, top = -1;
    node_pointer p;
    for (i = 0; i < n; i++)
        latest[i] = project;
    for (i = 0; i < n; i++)
        if (!graph[i].count) {
            graph[i].count = top;  top = i; }
    for (i = 0; i < n; i++) {
        if (top == -1) { printf("cycle"); break; }
        j = top;  top = graph[top].count;   /* reversed list */
        printf("%d ", j);
        for (p = graph[j].link; p; p = p->link) {
            k = p->vertex;                       /* k: predecessor */
            if (latest[k] > latest[j] - p->duration)
                latest[k] = latest[j] - p->duration;
            if (--graph[k].count == 0) {
                graph[k].count = top;  top = k;
            }
        }
    }
}

void print_slack(hdnodes graph[], int n)
{
    int i;
    node_pointer p;
    /* after computing earliest[] and latest[] */
    for (i = 0; i < n; i++)
        for (p = graph[i].link; p; p = p->link) {
            int early = earliest[i];
            int late  = latest[p->vertex] - p->duration;
            printf("<%d,%d> early=%d late=%d slack=%d%s\n",
                   i, p->vertex, early, late, late - early,
                   late == early ? " CRITICAL" : "");
        }
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

/* not on the slides: prints an array */
static void print_array(const char *name, const int a[], int n)
{
    int i;
    printf("%s =", name);
    for (i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void)
{
    /* a0..a10: <tail, head, duration> */
    static const int act[11][3] = {
        {0, 1, 6}, {0, 2, 4}, {0, 3, 5}, {1, 4, 1}, {2, 4, 1}, {3, 5, 2},
        {4, 6, 9}, {4, 7, 7}, {5, 7, 4}, {6, 8, 2}, {7, 8, 4}
    };
    static hdnodes graph[MAX_VERTICES], rev[MAX_VERTICES];
    int n = 9, i;

    for (i = 0; i < 11; i++)
        if (!add_edge(graph, act[i][0], act[i][1], act[i][2])) exit(1);
    if (!reverse_graph(graph, rev, n)) exit(1);   /* before the counts change */

    printf("forward: ");
    compute_earliest(graph, n);
    printf("\n");
    print_array("earliest", earliest, n);

    printf("backward: ");
    compute_latest(rev, n, earliest[n - 1]);
    printf("\n");
    print_array("latest", latest, n);

    print_slack(graph, n);
    free_lists(graph, n);
    free_lists(rev, n);
    return 0;
}

/* Note: the forward/backward lines end with a space. */
/* Expected output:
 * forward: 0 3 5 2 1 4 7 6 8 
 * earliest = 0 6 4 5 7 7 16 14 18
 * backward: 8 7 5 3 6 4 2 1 0 
 * latest = 0 6 6 8 7 10 16 14 18
 * <0,1> early=0 late=0 slack=0 CRITICAL
 * <0,2> early=0 late=2 slack=2
 * <0,3> early=0 late=3 slack=3
 * <1,4> early=6 late=6 slack=0 CRITICAL
 * <2,4> early=4 late=6 slack=2
 * <3,5> early=5 late=8 slack=3
 * <4,6> early=7 late=7 slack=0 CRITICAL
 * <4,7> early=7 late=7 slack=0 CRITICAL
 * <5,7> early=7 late=10 slack=3
 * <6,8> early=16 late=16 slack=0 CRITICAL
 * <7,8> early=14 late=14 slack=0 CRITICAL
 */
