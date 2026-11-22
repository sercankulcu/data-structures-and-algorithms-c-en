/* Linked merge sort from the exam question: the two recursive calls are the
 * arguments of merge, and C does not specify which one runs first. The
 * intermediate link values may vary with the compiler; the resulting list does
 * not. The example uses the keys a[1..9] = 42, 7, 18, -5, 27, 11, 55, 83, 30
 * from the notes (42, 7 and 55 stand where the question paper has ?); the
 * head of the resulting list is 4.
 * Slides: "Exam Question", "Exam Question (Question 3): Solution". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: element from "Sorting Alphabetic Data: Linked Merge Sort" */
typedef struct {
    int key;       /* + large data fields */
    int link;      /* index of the next item, 0 = end */
} element;

/* not on the slides: merge from "Code Trace: Linked merge" */
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

int mergesort(element a[], int L, int R) {
    int m;
    if (R <= L) return L;
    m = (R + L) / 2;
    return merge(a, mergesort(a, m + 1, R),
                    mergesort(a, L, m));
}

int main(void) {   /* not on the slides */
    int keys[] = {42, 7, 18, -5, 27, 11, 55, 83, 30};
    element a[10];
    a[0].key = 0;                          /* not used */
    a[0].link = 0;
    for (int k = 1; k <= 9; k++) {
        a[k].key = keys[k - 1];
        a[k].link = 0;
    }

    int head = mergesort(a, 1, 9);
    printf("head = %d\n", head);
    printf("list:");
    for (int p = head; p; p = a[p].link) printf(" %d", a[p].key);
    printf("\n");
    printf("link[1..9]:");
    for (int k = 1; k <= 9; k++) printf(" %d", a[k].link);
    printf("\n");
    return 0;
}


/* Expected output:
 * head = 4
 * list: -5 7 11 18 27 30 42 55 83
 * link[1..9]: 7 6 5 2 9 3 8 0 1
 */
