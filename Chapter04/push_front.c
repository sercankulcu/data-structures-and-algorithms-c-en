/* Singly linked list: traversal (print_list) and insertion at the front
 * (insert_front). 2, then 7 are inserted into an empty list (7 -> 2); then, as
 * in the trace in the notes, 5 (5 -> 7 -> 2).
 * Slides: "A Node: A Self-Referential struct", "Inserting at the Front, and
 * Passing by Address". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *node_ptr;  // pointer type first

struct node {
    int data;       // data field
    node_ptr link;    // address of the next node
};

void print_list(node_ptr p) {
    for (; p != NULL; p = p->link)
        printf("%d ", p->data);
    printf("\n");
}

bool insert_front(node_ptr *head, int x) {
    node_ptr temp = malloc(sizeof *temp);
    if (temp == NULL) return false;  // no memory
    temp->data = x;
    temp->link = *head;    // first keep the old head
    *head = temp;         // then move the head
    return true;
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
    node_ptr list = NULL;  // empty list
    insert_front(&list, 2);   // 2
    print_list(list);
    insert_front(&list, 7);   // 7 -> 2
    print_list(list);
    insert_front(&list, 5);   /* not on the slides: the trace from the notes, 5 -> 7 -> 2 */
    print_list(list);
    clear_list(&list);   /* not on the slides */
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 2
 * 7 2
 * 5 7 2
 */
