/* Bubble sort with early exit (bubble2): after a pass without swaps the array
 * is sorted and the function returns. The example is the array [2, 1, 3, 5, 4]
 * from the notes; the second pass ends without swaps and the function
 * returns.
 * Slide: "Code Trace: bubble2()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from the "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void bubble2(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int swapped = 0;    // any swap this pass?
        for (int j = R; j > i; j--)
            if (less(a[j], a[j - 1])) {
                SWAP(a[j], a[j - 1]);
                swapped = 1;
            }
        if (!swapped) return; // sorted: exit early
    }
}

int main(void) {   /* not on the slides */
    int a[] = {2, 1, 3, 5, 4};
    bubble2(a, 0, 4);
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 1 2 3 4 5 
 */
