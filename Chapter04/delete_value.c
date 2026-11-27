/* Deleting by value: prev advances together with p; if the head node is
 * deleted, *head changes. Example from the notes: from 3 -> 8 -> 1 -> 6 first 1,
 * then the head 3 are deleted, and finally 42, which is not in the list, is
 * searched for.
 * Slide: "Deletion: We Need the Node Before the Victim". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

bool delete_key(node_ptr *head, int x) {
    node_ptr prev = NULL, p = *head;
    while (p != NULL && p->data != x) {
        prev = p;
        p = p->link;
    }
    if (p == NULL) return false;        // x absent
    if (prev == NULL) *head = p->link;  // the head
    else prev->link = p->link;          // bypass
    free(p);
    return true;
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
    int a[] = {3, 8, 1, 6};
    int targets[] = {1, 3, 42};
    node_ptr list = build_list(a, 4);
    print_list(list);
    for (int i = 0; i < 3; i++) {
        bool result = delete_key(&list, targets[i]);
        printf("delete_key(%d) = %s: ", targets[i], result ? "true" : "false");
        print_list(list);
    }
    clear_list(&list);
    return 0;
}

/* Note: every line ends with a space. */
/* Expected output:
 * 3 8 1 6
 * delete_key(1) = true: 3 8 6
 * delete_key(3) = true: 8 6
 * delete_key(42) = false: 8 6
 */
