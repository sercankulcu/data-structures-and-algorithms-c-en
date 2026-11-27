/* Improved quicksort (quicksort3): the pivot is the median of three (a[L],
 * the middle item, a[R]), pieces smaller than M are left unsorted, and sort
 * makes a single insertion sort pass at the end. The example is the trace
 * from the notes: [8, 3, 5, 1, 9, 2, 7, 6, 4] with M = 3. After quicksort3
 * the array is almost sorted; insertion fixes the remaining two pairs.
 * Slides: "Improved Quicksort: Median-of-3 + Insertion Sort", "Code Trace:
 * quicksort3()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from Chapter 19 "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* not on the slides: partition from "Partitioning Invariant" slide */
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

/* not on the slides: insertion from Chapter 19 "Insertion Sort" slide */
void insertion(int a[], int L, int R) {
    for (int i = L + 1; i <= R; i++) {
        int v = a[i];      // to insert
        int j = i - 1;     // a[L..i-1] sorted
        while (j >= L && a[j] > v) {
            a[j + 1] = a[j]; // shift right
            j--;
        }
        a[j + 1] = v;
    }
}

/* on the slides M is 10; the trace in the notes (Table 20.7) uses M = 3. With
 * M = 10 quicksort3 returns at once on this nine-item array and insertion
 * does all the work. */
#define M 3     /* leave pieces smaller than this */
void quicksort3(int a[], int L, int R) {
    if (R - L <= M) return;
    SWAP(a[(L + R) / 2], a[R - 1]);
    if (a[R-1] < a[L]) SWAP(a[R-1], a[L]); // a[L] <= a[R-1]
    if (a[R] < a[L]) SWAP(a[R], a[L]);     // a[L] <= a[R]
    if (a[R] < a[R-1]) SWAP(a[R], a[R-1]); // a[R-1] <= a[R]
    int i = partition(a, L + 1, R - 1);
    quicksort3(a, L, i - 1);
    quicksort3(a, i + 1, R);
}
void sort(int a[], int L, int R) {
    quicksort3(a, L, R);
    insertion(a, L, R);   /* the small pieces left */
}

/* not on the slides: prints the array */
static void print_array(const char *name, const int a[], int n) {
    printf("%s", name);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int a[] = {8, 3, 5, 1, 9, 2, 7, 6, 4};
    quicksort3(a, 0, 8);           /* the first step of sort, alone */
    print_array("quicksort3: ", a, 9);

    int b[] = {8, 3, 5, 1, 9, 2, 7, 6, 4};
    sort(b, 0, 8);
    print_array("sort:", b, 9);
    return 0;
}


/* Expected output:
 * quicksort3:  1 3 2 4 6 5 7 8 9
 * sort: 1 2 3 4 5 6 7 8 9
 */
