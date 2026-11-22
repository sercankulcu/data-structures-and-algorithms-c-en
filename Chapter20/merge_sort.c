/* Merge sort (mergesort) and two-ended merge (merge): the left half is copied
 * into b as it is, the right half is copied in reverse; each half becomes the
 * sentinel of the other. The auxiliary array b is allocated once (merge_sort_alloc
 * in the notes). Examples from the notes: merge(a, b, 0, 2, 6) on
 * [3, 5, 7 | 4, 5, 6, 10] and mergesort on [89, 67, 59, 62, 23, 93, 24, 20,
 * 28, 60].
 * Slides: "Merge Sort" (two slides), "Code Trace: merge()", "Code Trace:
 * mergesort()". */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: malloc, free */

/* not on the slides: macro from Chapter 19 "Common Setup" slide */
#define less(A, B) ((A) < (B))

/* on the slides it is on the second slide; must be defined before mergesort */
void merge(int a[], int b[], int L, int m, int R) {
    int i, j, k;
    for (i = m + 1; i > L; i--) b[i - 1] = a[i - 1];
    for (j = m; j < R; j++) b[R + m - j] = a[j + 1];
    for (k = L; k <= R; k++)
        if (less(b[j], b[i]))
            a[k] = b[j--];
        else
            a[k] = b[i++];
}

void mergesort(int a[], int b[], int L, int R) {
    if (R <= L) return;
    int m = (R + L) / 2;
    mergesort(a, b, L, m);
    mergesort(a, b, m + 1, R);
    merge(a, b, L, m, R);
}

/* not on the slides: the wrapper from the notes, allocates b once */
int merge_sort_alloc(int a[], int n) {
    int *b = malloc(n * sizeof *b);   /* same size as a */
    if (b == NULL) return 0;          /* no memory: not sorted */
    mergesort(a, b, 0, n - 1);
    free(b);
    return 1;
}

/* not on the slides: prints the array */
static void print_array(const char *name, const int a[], int n) {
    printf("%s", name);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int a[] = {3, 5, 7, 4, 5, 6, 10};
    int b[7];
    merge(a, b, 0, 2, 6);
    print_array("merge:    ", a, 7);
    print_array("b:        ", b, 7);   /* after the copy: left ascending, right reversed */

    int c[] = {89, 67, 59, 62, 23, 93, 24, 20, 28, 60};
    if (!merge_sort_alloc(c, 10)) return 1;
    print_array("mergesort:", c, 10);
    return 0;
}


/* Expected output:
 * merge:     3 4 5 5 6 7 10
 * b:         3 5 7 10 6 5 4
 * mergesort: 20 23 24 28 59 60 62 67 89 93
 */
