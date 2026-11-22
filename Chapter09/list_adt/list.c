/* not on the slides: implementation of the list.h interface with a dynamic
 * array (the version in the lecture notes). The capacity starts at 4 and
 * doubles when the array is full. struct list is defined only in this
 * file (opaque type). */
#include <stdlib.h>
#include "list.h"

// list.c: struct list is defined only here (opaque type)
struct list {
    int *a;                             // array on the heap
    int n, cap;                         // item count, capacity
};

List *list_create(void) {
    List *L = malloc(sizeof *L);
    if (L == NULL) return NULL;
    L->n = 0;
    L->cap = 4;
    L->a = malloc(L->cap * sizeof *L->a);
    if (L->a == NULL) { free(L); return NULL; }
    return L;
}

void list_destroy(List *L) {
    if (L) { free(L->a); free(L); }
}

int list_length(const List *L) { return L->n; }

bool list_get(const List *L, int i, int *x) {
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    return true;
}

bool list_insert(List *L, int i, int x) {
    int k;
    if (i < 0 || i > L->n) return false;
    if (L->n == L->cap) {               // full: double it
        int *bigger = realloc(L->a, 2 * L->cap * sizeof *L->a);
        if (bigger == NULL) return false; // the old array stays in place
        L->a = bigger;
        L->cap *= 2;
    }
    for (k = L->n; k > i; k--)
        L->a[k] = L->a[k - 1];
    L->a[i] = x;
    L->n++;
    return true;
}

bool list_delete(List *L, int i, int *x) {
    int k;
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    for (k = i; k < L->n - 1; k++)
        L->a[k] = L->a[k + 1];
    L->n--;
    return true;
}

int list_find(const List *L, int x) {
    for (int k = 0; k < L->n; k++)
        if (L->a[k] == x) return k;
    return -1;
}
