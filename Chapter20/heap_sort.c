/* Heap sort: the array a[1..n] is read as a complete binary tree (children
 * 2i, 2i+1). First a max-heap is built bottom-up, then the largest item at
 * the root is moved to the end and the heap is repaired with heapify. The
 * example is Horowitz's array [26, 5, 77, 1, 61, 11, 59, 15, 48, 19] from the
 * notes; main also writes out the build phase separately.
 * Slides: "Heap Sort", "Code Trace: The Sorting Phase, SWAP + heapify". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macro from Chapter 19 "Common Setup" slide */
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void heapify(int a[], int root, int n) {
    int t = a[root], j;
    for (j = 2 * root; j <= n; j *= 2) {
        if (j < n && a[j] < a[j + 1]) j++; // larger
        if (t >= a[j]) break;   // t fits here
        a[j / 2] = a[j];        // move child up
    }
    a[j / 2] = t;
}
void heapsort(int a[], int n) {     /* a[1..n] */
    int i;
    for (i = n / 2; i >= 1; i--)     /* build heap */
        heapify(a, i, n);
    for (i = n - 1; i >= 1; i--) {   /* sort */
        SWAP(a[1], a[i + 1]);    /* largest to the end */
        heapify(a, 1, i);            /* fix the heap */
    }
}

/* not on the slides: prints a[1..n] */
static void print_array(const char *name, const int a[], int n) {
    printf("%s", name);
    for (int i = 1; i <= n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    /* a[0] is not used */
    int h[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    for (int i = 10 / 2; i >= 1; i--)   /* the build phase of heapsort */
        heapify(h, i, 10);
    print_array("heap:    ", h, 10);

    int a[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    heapsort(a, 10);
    print_array("heapsort:", a, 10);
    return 0;
}


/* Expected output:
 * heap:     77 61 59 48 19 11 26 15 1 5
 * heapsort: 1 5 11 15 19 26 48 59 61 77
 */
