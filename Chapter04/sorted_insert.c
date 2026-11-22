/* Inserting into a sorted linked list: prev and p advance together, the new
 * node goes between them; if prev stays NULL, head changes. Example from the
 * notes: into 2 -> 5 -> 9 insert 7, then 1 (front), 10 (back) and an existing 5
 * (in front of the old one).
 * Slide: "Inserting in the middle: Keep the Successor First, Then Link". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

void sorted_insert(node_ptr *head, node_ptr fresh) {
    node_ptr prev = NULL, p = *head;
    while (p != NULL && p->data < fresh->data) {
        prev = p;
        p = p->link;
    }
    fresh->link = p;
    if (prev == NULL) *head = fresh;  // at the front
    else prev->link = fresh;          // middle/end
}

/* not on the slides: allocates a node and stores its value (new_node from the "malloc and free" code) */
static node_ptr new_node(int x) {
    node_ptr p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yetmiyor\n");
        exit(1);
    }
    p->data = x;
    p->link = NULL;
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
    node_ptr list = NULL;
    node_ptr five;
    sorted_insert(&list, new_node(2));
    sorted_insert(&list, new_node(5));
    sorted_insert(&list, new_node(9));
    print_list(list);
    sorted_insert(&list, new_node(7));    /* middle */
    print_list(list);
    sorted_insert(&list, new_node(1));    /* front */
    print_list(list);
    sorted_insert(&list, new_node(10));   /* back */
    print_list(list);
    five = new_node(5);                   /* equal value */
    sorted_insert(&list, five);
    print_list(list);
    printf("new 5 before the old one: %s\n",
           five->link != NULL && five->link->data == 5 ? "yes" : "no");
    clear_list(&list);
    return 0;
}

/* Note: the number lines end with a space. */
/* Expected output:
 * 2 5 9
 * 2 5 7 9
 * 1 2 5 7 9
 * 1 2 5 7 9 10
 * 1 2 5 5 7 9 10
 * new 5 before the old one: yes
 */
