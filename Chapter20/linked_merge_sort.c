/* Linked (index-based) merge sort: records never move; the link field of each
 * record holds the index of the next item (0 = end). The data are in a[1..n],
 * a[0] serves as a temporary head in merge. The example uses the keys
 * a[1..10] = 71, 77, 122, 38, 119, 41, 22, 115, 43, 13 from the notes; the
 * head of the resulting list is 10.
 * Slides: "Sorting Alphabetic Data: Linked Merge Sort", "Code Trace: Linked
 * ...". */
#include <stdio.h>   /* not on the slides */

typedef struct {
    int key;       /* + large data fields */
    int link;      /* index of the next item, 0 = end */
} element;

int merge(element a[], int first, int second);   /* not on the slides: prototype */

int mergesort(element a[], int L, int R) {
    if (R <= L) return L;          /* one-item list */
    int m = (R + L) / 2;
    int right = mergesort(a, m + 1, R);
    int left = mergesort(a, L, m);
    return merge(a, left, right);  /* head index */
}

int merge(element a[], int first, int second) {
    int last = 0;               // a[0]: temp head
    int i1 = first, i2 = second;
    while (i1 && i2)
        if (a[i1].key <= a[i2].key) {
            a[last].link = i1; last = i1;
            i1 = a[i1].link;
        } else {
            a[last].link = i2; last = i2;
            i2 = a[i2].link;
        }
    a[last].link = i1 ? i1 : i2;
    return a[0].link;
}

int main(void) {   /* not on the slides */
    int keys[] = {71, 77, 122, 38, 119, 41, 22, 115, 43, 13};
    element a[11];
    a[0].key = 0;                          /* not used */
    a[0].link = 0;
    for (int k = 1; k <= 10; k++) {
        a[k].key = keys[k - 1];
        a[k].link = 0;                     /* every item is a list by itself */
    }

    int head = mergesort(a, 1, 10);
    printf("head = %d\n", head);
    printf("list:");
    for (int p = head; p; p = a[p].link) printf(" %d", a[p].key);
    printf("\n");
    printf("link[1..10]:");
    for (int k = 1; k <= 10; k++) printf(" %d", a[k].link);
    printf("\n");
    return 0;
}


/* Expected output:
 * head = 10
 * list: 13 22 38 41 43 71 77 115 119 122
 * link[1..10]: 2 8 0 6 3 9 4 5 1 7
 */
