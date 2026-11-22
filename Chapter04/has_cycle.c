/* Detecting a cycle in a list with Floyd's tortoise-and-hare method.
 * Example from the notes: 1 -> 2 -> 3 -> 4 -> 5 where the link of 5 wrongly
 * points to 3; the two pointers meet at 4 in round 3. The same list without
 * the cycle (link of 5 is NULL) gives false.
 * Slide: "Floyd's Cycle-Detection Algorithm (Tortoise and Hare)". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

bool has_cycle(node_ptr head) {
    node_ptr slow = head, fast = head;
    while (fast != NULL && fast->link != NULL) {
        slow = slow->link;         // 1 step
        fast = fast->link->link;    // 2 steps
        if (slow == fast) return true;
    }
    return false;
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
    node_ptr list = build_list(a, 5);
    node_ptr three = list->link->link;            /* 3 */
    node_ptr five = three->link->link;              /* 5 */

    printf("acyclic: %s\n", has_cycle(list) ? "true" : "false");
    five->link = three;                            /* 5 -> 3: cycle */
    printf("5 -> 3 cyclic: %s\n", has_cycle(list) ? "true" : "false");
    five->link = NULL;                          /* break the cycle, then free */
    clear_list(&list);
    return 0;
}

/* Expected output:
 * acyclic: false
 * 5 -> 3 cyclic: true
 */
