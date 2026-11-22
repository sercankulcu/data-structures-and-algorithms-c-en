/* Finding the middle node in one pass: the slow pointer moves one step, the
 * fast pointer two. Example from the notes: in 1 -> 2 -> 3 -> 4 -> 5 the middle
 * is 3; for an even length (1 -> 2 -> 3 -> 4) the second middle (3) is returned.
 * Slide: "The middle Node: Slow and Fast Pointers". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

node_ptr middle(node_ptr head) {
    node_ptr slow = head, fast = head;
    while (fast != NULL && fast->link != NULL) {
        slow = slow->link;        // 1 step
        fast = fast->link->link;   // 2 steps
    }
    return slow;
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

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    node_ptr odd = build_list(a, 5);
    node_ptr even = build_list(a, 4);
    printf("middle(1..5) = %d\n", middle(odd)->data);
    printf("middle(1..4) = %d\n", middle(even)->data);
    clear_list(&odd);
    clear_list(&even);
    return 0;
}

/* Expected output:
 * middle(1..5) = 3
 * middle(1..4) = 3
 */
