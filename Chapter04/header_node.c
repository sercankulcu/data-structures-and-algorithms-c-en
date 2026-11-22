/* Sorted insertion in a list with a header node: prev starts at the header and
 * is never NULL, so inserting at the front, middle, back or into an empty list
 * is the same two lines. Example from the notes: 8, 3, 5, 1, 9 into an empty
 * list with a header.
 * Slide: "The Header (Sentinel) Node". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

// sorted insert in a header list: no special case
void h_sorted_insert(node_ptr header, node_ptr fresh) {
    node_ptr prev = header;       // never NULL
    while (prev->link != NULL &&
           prev->link->data < fresh->data)
        prev = prev->link;
    fresh->link = prev->link;
    prev->link = fresh;
}

/* not on the slides: allocates a node */
static node_ptr new_node(int x) {
    node_ptr p = malloc(sizeof *p);
    if (p == NULL) exit(1);
    p->data = x;
    p->link = NULL;
    return p;
}

/* not on the slides: print_list, the traversal routine */
void print_list(node_ptr p) {
    for (; p != NULL; p = p->link)
        printf("%d ", p->data);
    printf("\n");
}

int main(void)
{
    struct node H = {0, NULL};               /* not on the slides: header node; its data is unused */
    int input[] = {8, 3, 5, 1, 9};
    node_ptr p, q;
    for (int i = 0; i < 5; i++) {
        h_sorted_insert(&H, new_node(input[i]));
        printf("%d inserted: ", input[i]);
        print_list(H.link);                      /* the real nodes follow the header */
    }
    for (p = H.link; p != NULL; p = q) {     /* not on the slides: cleanup */
        q = p->link;
        free(p);
    }
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 8 inserted: 8
 * 3 inserted: 3 8
 * 5 inserted: 3 5 8
 * 1 inserted: 1 3 5 8
 * 9 inserted: 1 3 5 8 9
 */
