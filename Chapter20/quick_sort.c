/* Quicksort (quicksort1) and partitioning (partition). partition puts the
 * pivot v = a[R] at the position where it will stand in the sorted array and
 * returns that position. The example is [37, 15, 24, 33, 49, 11, 51, 77, 72,
 * 48] from the notes: first a single call partition(a, 0, 9), then the same
 * array sorted completely with quicksort1.
 * Slides: "Quicksort", "Partitioning Invariant", "Code Trace: partition()",
 * "Code Trace: quicksort1()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from Chapter 19 "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

int partition(int a[], int L, int R);

void quicksort1(int a[], int L, int R) {
    if (R <= L) return;
    int i = partition(a, L, R);
    quicksort1(a, L, i - 1);
    quicksort1(a, i + 1, R);
}

int partition(int a[], int L, int R) {
    int i = L - 1, j = R, v = a[R]; // pivot a[R]
    for (;;) {
        while (less(a[++i], v))
            ;
        while (less(v, a[--j]))
            if (j == L) break;
        if (i >= j) break;
        SWAP(a[i], a[j]);
    }
    SWAP(a[i], a[R]);
    return i;
}

/* not on the slides: prints the array */
static void print_array(const int a[], int n) {
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int a[] = {37, 15, 24, 33, 49, 11, 51, 77, 72, 48};
    int i = partition(a, 0, 9);
    printf("partition(a, 0, 9) = %d:", i);
    print_array(a, 10);

    int b[] = {37, 15, 24, 33, 49, 11, 51, 77, 72, 48};
    quicksort1(b, 0, 9);
    printf("quicksort1:");
    print_array(b, 10);
    return 0;
}


/* Expected output:
 * partition(a, 0, 9) = 5: 37 15 24 33 11 48 51 77 72 49
 * quicksort1: 11 15 24 33 37 48 49 51 72 77
 */
