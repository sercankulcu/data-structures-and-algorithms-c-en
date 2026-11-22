/* Sequential representation in an array: the first n + 1 cells are the
 * starting indices, the remaining 2e cells are the neighbors. The neighbors
 * of i are vertex[vertex[i]] .. vertex[vertex[i+1] - 1].
 * Example from the notes: G4 (n = 8, e = 7, 23 cells); print_adj(vertex, 5)
 * prints "4 6".
 * Slide: "Sequential Array Step by Step". */
#include <stdio.h>

void print_adj(const int vertex[], int i)
{
    int k;
    for (k = vertex[i]; k < vertex[i + 1]; k++)
        printf("%d ", vertex[k]);
    printf("\n");
}

int main(void)
{
    /* not on the slides: the sequential representation of G4 (Figure 15.13) */
    static const int vertex[23] = {
        9, 11, 13, 15, 17, 18, 20, 22, 23,   /* 0..8: starting indices */
        1, 2,  0, 3,  0, 3,  1, 2,           /* 0, 1, 2, 3 */
        5,  4, 6,  5, 7,  6                  /* 4, 5, 6, 7 */
    };
    int i;
    for (i = 0; i < 8; i++) {
        printf("%d: ", i);
        print_adj(vertex, i);
    }
    return 0;
}

/* Note: print_adj leaves a space after every number. */
/* Expected output:
 * 0: 1 2
 * 1: 0 3
 * 2: 0 3
 * 3: 1 2
 * 4: 5
 * 5: 4 6
 * 6: 5 7
 * 7: 6
 */
