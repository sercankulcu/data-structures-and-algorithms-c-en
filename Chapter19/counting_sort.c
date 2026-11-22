/* Counting sort (counting_sort): the values are integers in 0..k. L1 clears
 * the counters, L2 counts, L3 accumulates (c[x] = number of items less than or
 * equal to x), L4 scans the input from right to left and places the items
 * into b stably. The example is a = [3, 0, 6, 9, 4, 3, 10, 5], r = 7, k = 10
 * from the notes.
 * Slides: "Counting Sort", "Code Trace: ..." (counting and placing). */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: malloc, free */

int counting_sort(const int a[], int b[],
                  int r, int k) {
    int *c = malloc((k + 1) * sizeof *c);
    if (c == NULL) return -1;
    for (int i = 0; i <= k; i++) c[i] = 0;  // L1
    for (int j = 0; j <= r; j++) c[a[j]]++; // L2
    for (int i = 1; i <= k; i++)            // L3
        c[i] += c[i - 1];
    for (int j = r; j >= 0; j--) {          // L4
        b[c[a[j]] - 1] = a[j];
        c[a[j]]--;
    }
    free(c);
    return 0;
}

int main(void) {   /* not on the slides */
    const int a[] = {3, 0, 6, 9, 4, 3, 10, 5};
    int b[8];
    if (counting_sort(a, b, 7, 10) != 0) return 1;
    for (int i = 0; i < 8; i++) printf("%d ", b[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 0 3 3 4 5 6 9 10 
 */
