/* Linked implementation of the list: ll_insert keeps a pointer to pointer
 * (pp) holding the address of the link that will change; inserting at the
 * head and in the middle is the same code.
 * Example: 7, 4, 2 are inserted at positions 0, 0 and 2 (giving 4 7 2),
 * then 9 is inserted at position 1; positions 6 and -1 are rejected.
 * Slide: "Linked Implementation: a Pointer to a Pointer". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free */
#include <stdbool.h>  /* not on the slides: bool */

typedef struct node *node_pointer;
struct node { int data; node_pointer link; };
typedef struct { node_pointer head; int n; } LinkedList;

bool ll_insert(LinkedList *L, int i, int x) {
    node_pointer *pp = &L->head, new_node;
    if (i < 0 || i > L->n) return false;
    while (i-- > 0)
        pp = &(*pp)->link;       // walk to link i
    new_node = malloc(sizeof *new_node);
    if (new_node == NULL) return false;
    new_node->data = x;
    new_node->link = *pp;
    *pp = new_node;              // head or middle: same
    L->n++;
    return true;
}

/* not on the slides: prints the list */
static void show(const LinkedList *L)
{
    node_pointer p;
    for (p = L->head; p; p = p->link)
        printf(p == L->head ? "%d" : " -> %d", p->data);
    printf(" (n = %d)\n", L->n);
}

/* not on the slides: gives the nodes back */
static void ll_clear(LinkedList *L)
{
    node_pointer p, q;
    for (p = L->head; p; p = q) { q = p->link; free(p); }
    L->head = NULL;
    L->n = 0;
}

int main(void)
{
    LinkedList B = { NULL, 0 };

    ll_insert(&B, 0, 7);
    ll_insert(&B, 0, 4);
    ll_insert(&B, 2, 2);
    show(&B);
    printf("ll_insert(&B, 1, 9) = %d\n", ll_insert(&B, 1, 9));
    show(&B);
    printf("ll_insert(&B, 6, 5) = %d\n", ll_insert(&B, 6, 5));
    printf("ll_insert(&B, -1, 5) = %d\n", ll_insert(&B, -1, 5));
    ll_clear(&B);
    return 0;
}

/* Expected output:
 * 4 -> 7 -> 2 (n = 3)
 * ll_insert(&B, 1, 9) = 1
 * 4 -> 9 -> 7 -> 2 (n = 4)
 * ll_insert(&B, 6, 5) = 0
 * ll_insert(&B, -1, 5) = 0
 */
