/* Concatenating two lists: find the last node of L1 and link it to L2.
 * Example from the notes: L1 = 1 -> 4, L2 = 6 -> 9; result 1 -> 4 -> 6 -> 9.
 * A call with an empty L1 returns L2.
 * Slide: "Concatenating Two Lists End to End". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

// links L2 to the end of L1, returns the head
node_ptr concat(node_ptr L1, node_ptr L2) {
    node_ptr p;
    if (L1 == NULL) return L2;
    if (L2 != NULL) {
        for (p = L1; p->link != NULL; p = p->link)
            ;                   // last node of L1
        p->link = L2;
    }
    return L1;
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
    int a[] = {1, 4};
    int b[] = {6, 9};
    node_ptr L1 = build_list(a, 2);
    node_ptr L2 = build_list(b, 2);
    node_ptr L = concat(L1, L2);
    print_list(L);
    L = concat(NULL, L);           /* empty L1 */
    print_list(L);
    clear_list(&L);                 /* the nodes of L1 and L2 are now in one list */
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 1 4 6 9
 * 1 4 6 9
 */
