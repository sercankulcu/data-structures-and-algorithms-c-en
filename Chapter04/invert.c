/* Reversing a linked list in place: no new nodes and no copies, only the
 * direction of the links changes (three pointers r, q, p). Example from the
 * notes: the list 10 -> 20 -> 30 becomes 30 -> 20 -> 10; a second application
 * restores the original; nothing happens on an empty list.
 * Slide: "The Same Job, Iteratively" (invert). */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

void invert(node_ptr *list) {
    node_ptr r, p = *list, q = NULL;
    while (p) {
        r = q;         // r trails q
        q = p;         // q trails p
        p = p->link;    // advance p
        q->link = r;    // reverse the link
    }
    *list = q;         // last node is the head
}

/* not on the slides: builds a list from an array (appending at the end) */
static node_ptr build_list(const int a[], int n) {
    node_ptr head = NULL, *tail = &head;
    for (int i = 0; i < n; i++) {
        node_ptr p = malloc(sizeof *p);
        if (p == NULL) exit(1);
        p->data = a[i];
        p->link = NULL;
        *tail = p;
        tail = &p->link;
    }
    return head;
}

/* not on the slides: print_list, the traversal routine */
void print_list(node_ptr p) {
    for (; p != NULL; p = p->link)
        printf("%d ", p->data);
    printf("\n");
}

/* not on the slides: frees the whole list */
static void clear_list(node_ptr *list) {
    while (*list != NULL) {
        node_ptr p = *list;
        *list = p->link;
        free(p);
    }
}

int main(void)
{
    int a[] = {10, 20, 30};
    node_ptr list = build_list(a, 3);
    node_ptr empty = NULL;
    print_list(list);
    invert(&list);
    print_list(list);
    invert(&list);
    print_list(list);
    invert(&empty);
    printf("empty list: %s\n", empty == NULL ? "NULL" : "?");
    clear_list(&list);
    return 0;
}

/* Note: the number lines end with a space. */
/* Expected output:
 * 10 20 30
 * 30 20 10
 * 10 20 30
 * empty list: NULL
 */
