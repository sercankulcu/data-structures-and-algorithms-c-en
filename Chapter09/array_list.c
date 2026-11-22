/* Implementing the list with an array (sequential layout): array_insert
 * shifts items right to make room, array_delete shifts left to close the
 * gap. Example list [4, 7, 2]; 9 is inserted at position 1, then the
 * first item is deleted; invalid positions are rejected with false.
 * Slides: "Array Implementation (Sequential Mapping)", "Code Trace: array_insert(&L, 1, 9)". */
#include <stdio.h>
#include <stdbool.h>  /* not on the slides: bool */

#define CAPACITY 100
typedef struct {
    int a[CAPACITY];
    int n;                  // item count
} ArrayList;

bool array_delete(ArrayList *L, int i, int *x) {
    int k;
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    for (k = i; k < L->n - 1; k++)
        L->a[k] = L->a[k + 1];      // shift left
    L->n--;
    return true;
}

bool array_insert(ArrayList *L, int i, int x) {
    int k;
    if (L->n == CAPACITY || i < 0 || i > L->n)
        return false;          // full/invalid
    for (k = L->n; k > i; k--)
        L->a[k] = L->a[k - 1];     // shift right
    L->a[i] = x;
    L->n++;
    return true;
}

/* not on the slides: prints the list */
static void show(const ArrayList *L)
{
    int k;
    printf("[");
    for (k = 0; k < L->n; k++)
        printf(k ? ", %d" : "%d", L->a[k]);
    printf("] n = %d\n", L->n);
}

int main(void)
{
    ArrayList L = { {4, 7, 2}, 3 };
    int x = 0, r;

    printf("start: ");
    show(&L);

    r = array_insert(&L, 1, 9);
    printf("array_insert(&L, 1, 9) = %d: ", r);
    show(&L);

    r = array_delete(&L, 0, &x);
    printf("array_delete(&L, 0, &x) = %d, x = %d: ", r, x);
    show(&L);

    r = array_insert(&L, 5, 1);
    printf("array_insert(&L, 5, 1) = %d\n", r);
    r = array_delete(&L, 3, &x);
    printf("array_delete(&L, 3, &x) = %d\n", r);
    return 0;
}

/* Expected output:
 * start: [4, 7, 2] n = 3
 * array_insert(&L, 1, 9) = 1: [4, 9, 7, 2] n = 4
 * array_delete(&L, 0, &x) = 1, x = 4: [9, 7, 2] n = 3
 * array_insert(&L, 5, 1) = 0
 * array_delete(&L, 3, &x) = 0
 */
