/* Bubble sort (bubble): in every pass neighbors are compared from right to
 * left and the smallest item rises to the left. The example is the array
 * [7, 2, 9, 5, 1] from the trace in the notes.
 * Slide: "Bubble Sort". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macro from the "Common Setup" slide */
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void bubble(int a[], int L, int R) {
    int i, j;
    for (i = L; i < R; i++)
        for (j = R; j > i; j--)
            if (a[j] < a[j-1]) SWAP(a[j], a[j-1]);
}

int main(void) {   /* not on the slides */
    int a[] = {7, 2, 9, 5, 1};
    bubble(a, 0, 4);
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 1 2 5 7 9 
 */
