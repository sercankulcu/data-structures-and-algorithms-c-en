/* Deleting the node after a given node: keep its address, fix the link, free
 * it. Example from the notes: in 5 -> 3 -> 8 -> 2 delete the node after 3 (8);
 * then try to delete the node after the last one (nothing happens).
 * Slide: "Deletion: We Need the Node Before the Victim". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

// deletes the node after prev from the list and
// from memory
void delete_after(node_ptr prev) {
    node_ptr victim = prev->link; // keep the address
    if (victim == NULL) return; // nothing to delete
    prev->link = victim->link;  // fix the link
    free(victim);               // free the leftover
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
    int a[] = {5, 3, 8, 2};
    node_ptr list = build_list(a, 4);
    print_list(list);
    delete_after(list->link);            /* the one after 3: 8 */
    print_list(list);
    delete_after(list->link->link);       /* 2 is the last node: nothing to delete */
    print_list(list);
    clear_list(&list);
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 5 3 8 2
 * 5 3 2
 * 5 3 2
 */
