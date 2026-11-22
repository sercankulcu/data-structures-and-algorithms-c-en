/* Insertion sort with a sentinel (insertion1): first a right-to-left pass
 * moves the smallest item to a[L]; since it is the sentinel, the inner loop
 * does not need the j >= L test. The example is the array [4, 3, 1, 2] from
 * the trace in the notes.
 * Slides: "Insertion Sort: Two Versions", "Code Trace: insertion1()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from the "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void insertion1(int a[], int L, int R) {
    for (int i = R; i > L; i--) // sentinel
        if (a[i] < a[i-1]) SWAP(a[i], a[i-1]);
    for (int i = L + 2; i <= R; i++) {
        int v = a[i], j = i;
        while (less(v, a[j - 1])) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

int main(void) {   /* not on the slides */
    int a[] = {4, 3, 1, 2};
    insertion1(a, 0, 3);
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 1 2 3 4 
 */
