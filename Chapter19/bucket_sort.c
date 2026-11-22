/* Bucket sort (bucket_sort): n real numbers in [0, 1) are scattered into n
 * buckets; every bucket is a linked list and a number is inserted into its
 * bucket in sorted order (with a pointer to a pointer). The nodes are taken
 * from a single pool array. The example is the 10-number input from the
 * notes.
 * Slide: "Bucket Sort: An Implementation in C". */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: calloc, malloc, free */

typedef struct bnode { double x; struct bnode *next; } bnode;

int bucket_sort(double a[], int n) {        /* 0 <= a[i] < 1 */
    bnode **bucket = calloc(n, sizeof *bucket);
    bnode *pool = malloc(n * sizeof *pool);
    if (!bucket || !pool) { free(bucket); free(pool); return -1; }
    for (int i = 0; i < n; i++) {           /* scatter + sorted insert */
        bnode **p = &bucket[(int)(a[i] * n)];
        while (*p && (*p)->x <= a[i]) p = &(*p)->next;
        pool[i].x = a[i]; pool[i].next = *p; *p = &pool[i];
    }
    int k = 0;                              /* gather the buckets */
    for (int b = 0; b < n; b++)
        for (bnode *q = bucket[b]; q; q = q->next) a[k++] = q->x;
    free(bucket); free(pool);
    return 0;
}

int main(void) {   /* not on the slides */
    double a[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    if (bucket_sort(a, 10) != 0) return 1;
    for (int i = 0; i < 10; i++) printf("%.2f ", a[i]);
    printf("\n");
    return 0;
}


/* Expected output (trailing space at the end of the line):
 * 0.12 0.17 0.21 0.23 0.26 0.39 0.68 0.72 0.78 0.94 
 */
