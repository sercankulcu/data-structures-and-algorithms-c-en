/* Circular linked list: the list is held by a pointer to its last node, the
 * first node is last->link. c_length counts one round with do-while;
 * c_push_front inserts at the front in O(1), and if *last = fresh is
 * assigned afterwards, the same node has been inserted at the back.
 * Example from the notes: the ring 3 -> 5 -> 8.
 * Slides: "A Circular List: The Last Node Points to the First", "Inserting at
 * the Front and Back of a Circular List". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

int c_length(node_ptr last) {
    int n = 0;
    node_ptr p = last;
    if (last == NULL) return 0;   // empty list
    do {
        n++;
        p = p->link;
    } while (p != last);          // full circle
    return n;
}

void c_push_front(node_ptr *last, node_ptr fresh) {
    if (*last == NULL) {           // empty list
        *last = fresh;
        fresh->link = fresh;        // points to itself
    } else {
        fresh->link = (*last)->link;  // old first node
        (*last)->link = fresh;
    }
}

/* not on the slides: allocates a node */
static node_ptr new_node(int x) {
    node_ptr p = malloc(sizeof *p);
    if (p == NULL) exit(1);
    p->data = x;
    p->link = NULL;
    return p;
}

/* not on the slides: prints one round starting at the first node (last->link) */
static void c_print(node_ptr last) {
    node_ptr p;
    if (last != NULL) {
        p = last->link;
        do {
            printf("%d ", p->data);
            p = p->link;
        } while (p != last->link);
    }
    printf("(length %d)\n", c_length(last));
}

/* not on the slides: opens the ring and frees every node */
static void c_clear(node_ptr *last) {
    node_ptr p, q;
    if (*last == NULL) return;
    p = (*last)->link;
    (*last)->link = NULL;
    while (p != NULL) {
        q = p->link;
        free(p);
        p = q;
    }
    *last = NULL;
}

int main(void)
{
    node_ptr last = NULL;
    node_ptr fresh;
    c_print(last);
    c_push_front(&last, new_node(8));   /* empty list: points to itself */
    c_push_front(&last, new_node(5));
    c_push_front(&last, new_node(3));
    c_print(last);
    c_push_front(&last, new_node(1));   /* insert at the front */
    c_print(last);
    fresh = new_node(9);               /* insert at the back */
    c_push_front(&last, fresh);
    last = fresh;
    c_print(last);
    c_clear(&last);
    return 0;
}

/* Expected output:
 * (length 0)
 * 3 5 8 (length 3)
 * 1 3 5 8 (length 4)
 * 1 3 5 8 9 (length 5)
 */
