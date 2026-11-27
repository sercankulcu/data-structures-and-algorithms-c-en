/* Searching a linked list by value ((search)) and reaching a node by 0-based
 * position (nth). Example from the notes: list 4 -> 1 -> 6 -> 5, positions 0, 3, 4.
 * Slide: "Searching and Reaching the i-Th Node". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

node_ptr search(node_ptr p, int x) {
    while (p != NULL && p->data != x)
        p = p->link;
    return p;               // NULL if not found
}

node_ptr nth(node_ptr p, int i) {  // 0-based
    while (p != NULL && i-- > 0)
        p = p->link;
    return p;               // NULL if i >= length
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

/* not on the slides: frees the whole list */
static void clear_list(node_ptr *list) {
    while (*list != NULL) {
        node_ptr p = *list;
        *list = p->link;
        free(p);
    }
}

/* not on the slides: prints the node found, or NULL */
static void show(const char *what, node_ptr p) {
    if (p == NULL) printf("%s -> NULL\n", what);
    else printf("%s -> %d\n", what, p->data);
}

int main(void)
{
    int a[] = {4, 1, 6, 5};
    node_ptr list = build_list(a, 4);
    show("search(list, 6)", search(list, 6));
    show("search(list, 42)", search(list, 42));
    show("nth(list, 0)", nth(list, 0));
    show("nth(list, 3)", nth(list, 3));
    show("nth(list, 4)", nth(list, 4));
    clear_list(&list);
    return 0;
}

/* Expected output:
 * search(list, 6) -> 6
 * search(list, 42) -> NULL
 * nth(list, 0) -> 4
 * nth(list, 3) -> 5
 * nth(list, 4) -> NULL
 */
