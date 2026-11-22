/* Gathering malloc and its check in new_node; inserting after a given node
 * (insert_after). The list 12 -> 7 -> 25 is built with this function, then, as
 * in the example in the notes, 9 is inserted after 7: 12 -> 7 -> 9 -> 25.
 * Slides: "Inserting in the middle: Keep the Successor First, Then Link",
 * "A Node: A Self-Referential struct" (new_node). */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

node_ptr new_node(int x) {
    node_ptr p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yetmiyor yetmiyoor...\n");
        exit(1);
    }
    p->data = x;
    p->link = NULL;
    return p;
}

// adds a node holding x after prev
node_ptr insert_after(node_ptr prev, int x) {
    node_ptr p = new_node(x);  // malloc + check
    if (prev != NULL) {      // middle or end
        p->link = prev->link;
        prev->link = p;
    }                          // else alone
    return p;
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
    node_ptr list = insert_after(NULL, 12);   /* alone: a new list */
    node_ptr seven = insert_after(list, 7);    /* at the end */
    insert_after(seven, 25);                    /* at the end */
    print_list(list);
    insert_after(seven, 9);                     /* in the middle */
    print_list(list);
    clear_list(&list);
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 12 7 25
 * 12 7 9 25
 */
