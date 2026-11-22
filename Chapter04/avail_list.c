/* Available space list: get_node takes a node from avail or from malloc,
 * ret_node puts it back, cerase returns a whole circular list to avail in O(1).
 * Example from the notes: three nodes taken from an eight-node avail form the
 * circular list 3 -> 5 -> 8; after cerase avail starts with 3, 5, 8.
 * Slide: "The Available Space List". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

node_ptr avail = NULL;        // available nodes

node_ptr get_node(void) {
    node_ptr p;
    if (avail != NULL) {         // take from the list
        p = avail;
        avail = avail->link;
    } else {                     // else ask the system
        p = malloc(sizeof *p);
        if (p == NULL) exit(1);
    }
    return p;
}

void ret_node(node_ptr p) {      // instead of free
    p->link = avail;
    avail = p;
}

// return a circular list to avail in O(1)
void cerase(node_ptr *last) {
    node_ptr first;
    if (*last != NULL) {
        first = (*last)->link;     // first node
        (*last)->link = avail;   // open the ring
        avail = first;
        *last = NULL;
    }
}

/* not on the slides: length of the avail chain */
static int avail_length(void) {
    int n = 0;
    for (node_ptr p = avail; p != NULL; p = p->link) n++;
    return n;
}

int main(void)
{
    node_ptr d[8], a, b, c, last, p, q;
    int i;
    for (i = 0; i < 8; i++) d[i] = get_node();   /* avail is empty: all eight come from malloc */
    for (i = 0; i < 8; i++) ret_node(d[i]);
    printf("avail: %d nodes\n", avail_length());

    a = get_node(); a->data = 3;                /* get_node does not initialize the fields */
    b = get_node(); b->data = 5;
    c = get_node(); c->data = 8;
    a->link = b; b->link = c; c->link = a;          /* 3 -> 5 -> 8 circular */
    last = c;
    printf("list built, avail: %d nodes\n", avail_length());

    cerase(&last);
    printf("after cerase avail: %d nodes, first three: %d %d %d, last %s NULL\n",
           avail_length(), avail->data, avail->link->data,
           avail->link->link->data, last == NULL ? "==" : "!=");

    p = get_node();                              /* reuse */
    ret_node(p);
    q = get_node();
    printf("released node handed out again: %s\n", q == p ? "yes" : "no");
    ret_node(q);

    while (avail != NULL) {                      /* not on the slides: return to the system */
        p = avail;
        avail = avail->link;
        free(p);
    }
    return 0;
}

/* Expected output:
 * avail: 8 nodes
 * list built, avail: 5 nodes
 * after cerase avail: 8 nodes, first three: 3 5 8, last == NULL
 * released node handed out again: yes
 */
