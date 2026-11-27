/* Dijkstra (shortest_path): in every round the nearest unmarked vertex
 * (choose) is finalized and its neighbors are relaxed; pred[] holds the
 * shortest-path tree, print_path writes the path recursively from the source
 * to the target. Cost matrix, O(n^2).
 * Example from the notes: the 6-vertex graph (Horowitz-Sahni). Source 0:
 * 2 -> 10, 3 -> 25, 1 -> 45, 4 -> 45, no path to 5. Source 2: 0 -> 20,
 * 3 -> 15, 1 -> 35, 4 -> 45.
 * Slides: "C Code: The Cost Matrix and choose", "shortest_path(): The Main
 * Function", "Code Trace: ...", "Finding the Path: The Predecessor Array". */
#include <stdio.h>
#include <limits.h>
#define MAX_VERTICES 6
#define INF 1000         /* no edge */
#define TRUE  1          /* not on the slides: TRUE/FALSE from Chapter 15 */
#define FALSE 0
int cost[][MAX_VERTICES] = {
    {   0,   50,  10, 1000,   45, 1000},
    {1000,    0,  15, 1000,   10, 1000},
    {  20, 1000,   0,   15, 1000, 1000},
    {1000,   20, 1000,   0,   35, 1000},
    {1000, 1000, 1000,  30,    0, 1000},   /* missing row */
    {1000, 1000, 1000,   3, 1000,    0}};  /* 100 -> 1000 */
int choose(int dist[], int n, short found[])
{
    int i, min = INT_MAX, pos = -1;
    for (i = 0; i < n; i++)
        if (dist[i] < min && !found[i]) {
            min = dist[i];  pos = i;
        }
    return pos;
}

void shortest_path(int v, int cost[][MAX_VERTICES],
                   int dist[], int pred[],
                   int n, short found[])
{
    int i, u, w;
    for (i = 0; i < n; i++) {                  /* A1 */
        found[i] = FALSE;
        dist[i] = cost[v][i];
        pred[i] = v;               /* kept for the path */
    }
    found[v] = TRUE;  dist[v] = 0;
    for (i = 2; i < n; i++) {        /* n-2 rounds */
        u = choose(dist, n, found);
        if (u < 0) break;            /* none left */
        found[u] = TRUE;
        for (w = 0; w < n; w++)
            if (!found[w] &&
                dist[u] + cost[u][w] < dist[w]) {
                dist[w] = dist[u] + cost[u][w];
                pred[w] = u;
            }
    }
}

void print_path(int pred[], int s, int h)
{
    if (h == s) {
        printf("%d", s);
        return;
    }
    print_path(pred, s, pred[h]);   /* pred first */
    printf(" -> %d", h);
}

/* not on the slides: prints all results for one source; pred[] is
 * meaningless for an unreachable vertex, so dist is checked first */
static void print_result(int s)
{
    int dist[MAX_VERTICES], pred[MAX_VERTICES], t;
    short found[MAX_VERTICES];
    shortest_path(s, cost, dist, pred, MAX_VERTICES, found);
    printf("source %d:\n", s);
    for (t = 0; t < MAX_VERTICES; t++) {
        if (dist[t] >= INF) {
            printf("  %d: no path\n", t);
            continue;
        }
        printf("  %d: %d  ", t, dist[t]);
        print_path(pred, s, t);
        printf("\n");
    }
}

int main(void)
{
    print_result(0);
    print_result(2);
    return 0;
}


/* Expected output:
 * source 0:
 *   0: 0  0
 *   1: 45  0 -> 2 -> 3 -> 1
 *   2: 10  0 -> 2
 *   3: 25  0 -> 2 -> 3
 *   4: 45  0 -> 4
 *   5: no path
 * source 2:
 *   0: 20  2 -> 0
 *   1: 35  2 -> 3 -> 1
 *   2: 0  2
 *   3: 15  2 -> 3
 *   4: 45  2 -> 3 -> 1 -> 4
 *   5: no path
 */
