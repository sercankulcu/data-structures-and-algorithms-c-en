/* A program that uses the List ADT only through its interface: it inserts
 * five values at the front, deletes the item at position 2, and prints the
 * length, the deleted value and the position of 20. Changing the
 * implementation (list.c) does not affect this file.
 * Slide: "The List ADT: What It Does, with the How Hidden" (the client program is from the notes). */
#include <stdio.h>
#include "list.h"                       // interface only

int main(void) {
    List *L = list_create();
    int x, k;
    if (L == NULL) return 1;
    for (k = 1; k <= 5; k++)
        list_insert(L, 0, 10 * k);      // always at the front: 50 40 30 20 10
    list_delete(L, 2, &x);              // removes 30
    printf("%d %d %d\n", list_length(L), x, list_find(L, 20));
    list_destroy(L);
    return 0;
}

/* Expected output:
 * 4 30 2
 */
