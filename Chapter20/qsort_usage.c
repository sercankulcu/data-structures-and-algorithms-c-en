/* qsort from the C library and the comparison function ascending. The return
 * value (x > y) - (x < y) never overflows (x - y can).
 * Slide: "qsort Usage". */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: qsort */

int ascending(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;
    return (x > y) - (x < y);  // -1, 0, +1
}
int main(void) {
    int a[] = {37, 15, 24, 33, 49};
    size_t n = sizeof a / sizeof a[0];
    qsort(a, n, sizeof a[0], ascending);
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}

/* Expected output (trailing space at the end of the line, no newline):
 * 15 24 33 37 49 
 */
