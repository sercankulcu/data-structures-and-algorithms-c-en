/* Shell sort (shell_sort): insertion sort with gap h = n/2, n/4, ..., 1. The
 * example is the array [35, 33, 42, 10, 14, 19, 27, 44] from the trace in the
 * notes; after the passes h = 4 and h = 2 the array is
 * [14, 19, 27, 10, 35, 33, 42, 44] and [14, 10, 27, 19, 35, 33, 42, 44].
 * Slide: "Code Trace: shell_sort()". */
#include <stdio.h>   /* not on the slides */

void shell_sort(int a[], int n) {
    for (int h = n / 2; h > 0; h /= 2) // gap
        for (int i = h; i < n; i++) {
            int v = a[i], j = i;
            while (j >= h && a[j - h] > v) {
                a[j] = a[j - h];    // shift back h
                j -= h;
            }
            a[j] = v;
        }
}

int main(void) {   /* not on the slides */
    int a[] = {35, 33, 42, 10, 14, 19, 27, 44};
    shell_sort(a, 8);
    for (int i = 0; i < 8; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 10 14 19 27 33 35 42 44 
 */
