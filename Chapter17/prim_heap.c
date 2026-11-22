/* Prim with adjacency lists and a binary min-heap, O(e log n): when lowcost
 * decreases the old entry is not removed; another entry with the new key is
 * pushed instead, and a later entry of a vertex already in the tree is stale
 * and skipped.
 * Example from the notes: the seven-bay graph; 10 entries are pushed, 10 are
 * popped, 3 of them stale; the tree costs 99.
 * Slide: "Speeding Up Prim with a Heap (Extra Topic)". */
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000      /* not on the slides: the constant from the notes */
#define MAX_VERTICES 50  /* not on the slides: the constant from Chapter 15 */

/* not on the slides: weighted adjacency list (Chapter 15, "Weighted Graph
 * Representation"), with the header name used on the slide */
typedef struct node *node_pointer;
typedef struct node {
    int vertex;
    int weight;         /* cost of the edge */
    node_pointer link;
} node;
node_pointer graph[MAX_VERTICES];

/* not on the slides: the binary min-heap from the notes */
typedef struct { int vertex, key; } entry;
typedef struct {
    entry *a;          /* a[1..size]: root a[1] */
    int size, capacity;
} heap;
int heap_empty(const heap *H) { return H->size == 0; }
void heap_push(heap *H, int vertex, int key)
{
    int i = ++H->size;                      /* capacity >= 2e + 1 */
    while (i > 1 && H->a[i / 2].key > key) {
        H->a[i] = H->a[i / 2];              /* move the parent down */
        i /= 2;
    }
    H->a[i].vertex = vertex;  H->a[i].key = key;
}
int heap_pop_min(heap *H)
{
    int root = H->a[1].vertex;
    entry last = H->a[H->size--];
    int i = 1, c = 2;
    while (c <= H->size) {
        if (c < H->size && H->a[c + 1].key < H->a[c].key) c++;
        if (last.key <= H->a[c].key) break;
        H->a[i] = H->a[c];                  /* move the smaller child up */
        i = c;  c *= 2;
    }
    H->a[i] = last;
    return root;
}

/* not on the slides: adds (v, w) at the front of graph[u] */
static void add_edge(int u, int v, int w)
{
    node_pointer p = malloc(sizeof(node));
    if (p == NULL) exit(1);
    p->vertex = v;  p->weight = w;
    p->link = graph[u];
    graph[u] = p;
}

int main(void)
{
    /* not on the slides: the example graph, variables and the heap */
    static const int edges[9][3] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int n = 7, e = 9, u, v, total = 0;
    int lowcost[MAX_VERTICES], closest[MAX_VERTICES], in_tree[MAX_VERTICES];
    node_pointer p;
    heap pq, *H = &pq;

    for (v = 0; v < e; v++) {
        add_edge(edges[v][0], edges[v][1], edges[v][2]);
        add_edge(edges[v][1], edges[v][0], edges[v][2]);
    }
    for (v = 0; v < n; v++) {
        lowcost[v] = INF;  closest[v] = -1;  in_tree[v] = 0;
    }
    lowcost[0] = 0;
    pq.capacity = 2 * e + 2;
    pq.size = 0;
    pq.a = malloc(pq.capacity * sizeof(entry));
    if (pq.a == NULL) exit(1);

    /* adjacency lists + min-heap (key = lowcost) */
    heap_push(H, 0, 0);
    while (!heap_empty(H)) {
        u = heap_pop_min(H);         /* O(log n) */
        if (in_tree[u]) continue;    /* stale entry */
        in_tree[u] = 1;
        for (p = graph[u]; p; p = p->link)
            if (!in_tree[p->vertex] &&
                p->weight < lowcost[p->vertex]) {
                lowcost[p->vertex] = p->weight;
                closest[p->vertex] = u;
                heap_push(H, p->vertex, p->weight);
            }
    }

    /* not on the slides: the tree edges and freeing the memory */
    for (v = 1; v < n; v++) {
        printf("(%d,%d) %d\n", closest[v], v, lowcost[v]);
        total += lowcost[v];
    }
    printf("total = %d\n", total);
    free(pq.a);
    for (v = 0; v < n; v++)
        while (graph[v]) {
            p = graph[v];
            graph[v] = p->link;
            free(p);
        }
    return 0;
}


/* Expected output:
 * (2,1) 16
 * (3,2) 12
 * (4,3) 22
 * (5,4) 25
 * (0,5) 10
 * (1,6) 14
 * total = 99
 */
