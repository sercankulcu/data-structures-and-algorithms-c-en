/* Inserting at the end of a singly linked list: the last node is found with
 * the condition p->link != NULL. Example from the notes: 5 is appended to
 * 4 -> 1 -> 6.
 * Slide: "Inserting at the Back: Finding the Last Node Is O(n)". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

bool insert_back(node_ptr *head, int x) {
    node_ptr p, temp = malloc(sizeof *temp);
    if (temp == NULL) return false;
    temp->data = x;
    temp->link = NULL;              // the new last node
    if (*head == NULL) { *head = temp; return true; }
    for (p = *head; p->link != NULL; p = p->link)
        ;                          // find the last node
    p->link = temp;
    return true;
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
    node_ptr list = NULL;
    insert_back(&list, 4);          /* empty-list branch */
    insert_back(&list, 1);
    insert_back(&list, 6);
    print_list(list);
    insert_back(&list, 5);
    print_list(list);
    clear_list(&list);
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 4 1 6
 * 4 1 6 5
 */
