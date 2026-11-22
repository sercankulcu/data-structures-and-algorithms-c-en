/* Circular doubly linked list with a header: insertion to the right of p
 * (dinsert) and O(1) deletion without a search (ddelete). At every step the
 * invariant p == p->llink->rlink == p->rlink->llink is checked.
 * Example from the notes: in H <-> 4 <-> 8 <-> H insert 6 to the right of 4;
 * then 6, 4 and 8 are deleted, and finally an attempt to delete the header is
 * rejected.
 * Slides: "The Doubly Linked List", "Deleting from a Doubly Linked List: No
 * Search for the Predecessor". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dnode *dnode_ptr;
struct dnode {
    dnode_ptr llink;   // previous
    int data;
    dnode_ptr rlink;   // next
};
// invariant: p == p->llink->rlink == p->rlink->llink

// inserts temp to the right of node p
void dinsert(dnode_ptr p, dnode_ptr temp) {
    temp->llink = p;
    temp->rlink = p->rlink;
    p->rlink->llink = temp;
    p->rlink = temp;
}

void ddelete(dnode_ptr header, dnode_ptr p) {
    if (p == header) {       // never delete the header
        fprintf(stderr, "Cannot delete header\n");
        return;
    }
    p->llink->rlink = p->rlink;
    p->rlink->llink = p->llink;
    free(p);
}

/* not on the slides: allocates a node */
static dnode_ptr new_dnode(int x) {
    dnode_ptr p = malloc(sizeof *p);
    if (p == NULL) exit(1);
    p->llink = p->rlink = p;
    p->data = x;
    return p;
}

/* not on the slides: prints forward and backward, checks the invariant */
static void print_dlist(dnode_ptr H) {
    dnode_ptr p;
    bool ok = true;
    printf("forward: H");
    for (p = H->rlink; p != H; p = p->rlink)
        printf(" %d", p->data);
    printf(" | backward: H");
    for (p = H->llink; p != H; p = p->llink)
        printf(" %d", p->data);
    p = H;
    do {
        if (p->llink->rlink != p || p->rlink->llink != p) ok = false;
        p = p->rlink;
    } while (p != H);
    printf(" | invariant %s\n", ok ? "holds" : "BROKEN");
}

int main(void)
{
    dnode_ptr H = new_dnode(0);      /* empty list: both links point to the header itself */
    dnode_ptr d4 = new_dnode(4), d6 = new_dnode(6), d8 = new_dnode(8);
    print_dlist(H);
    dinsert(H, d4);
    dinsert(d4, d8);
    print_dlist(H);
    dinsert(d4, d6);               /* 6 to the right of 4 */
    print_dlist(H);
    ddelete(H, d6);
    print_dlist(H);
    ddelete(H, d4);                 /* first real node */
    print_dlist(H);
    ddelete(H, d8);                 /* last real node */
    print_dlist(H);
    printf("H->llink == H: %s, H->rlink == H: %s\n",
           H->llink == H ? "yes" : "no", H->rlink == H ? "yes" : "no");
    fflush(stdout);                  /* not on the slides: keep the stderr line in order */
    ddelete(H, H);                  /* rejected */
    free(H);                         /* not on the slides */
    return 0;
}

/* Note: ddelete(H, H) writes "Cannot delete header" to stderr; only stdout is shown below. */
/* Expected output:
 * forward: H | backward: H | invariant holds
 * forward: H 4 8 | backward: H 8 4 | invariant holds
 * forward: H 4 6 8 | backward: H 8 6 4 | invariant holds
 * forward: H 4 8 | backward: H 8 4 | invariant holds
 * forward: H 8 | backward: H 8 | invariant holds
 * forward: H | backward: H | invariant holds
 * H->llink == H: yes, H->rlink == H: yes
 */
