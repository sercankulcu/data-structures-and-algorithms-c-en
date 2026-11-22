/* Returning a whole list to memory: the recursive free_list (first advance the
 * head, then free the old head, continue with the same address) and the
 * iterative clear_list. Both versions set the caller's list variable to NULL.
 * Example from the notes: 4 -> 9.
 * Slides: "Exam Question: Which One Is Right?" (two versions), "The Same Job,
 * Iteratively". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: node type from the "A Node" slide */
typedef struct node *node_ptr;
struct node {
    int data;
    node_ptr link;
};

/* Both versions in the exam question take list_ptr *list (list_ptr == node_ptr).
 * The left version is wrong and is not run:
 *
 *   void free_list( list_ptr *list ){
 *       node_ptr p = *list;
 *       if( *list ){
 *           p = *list->link;      // does not compile: read as *(list->link)
 *           free(*list);
 *           free_list(&p);        // address of the local p: the caller's list
 *   }}                            // does not change, it stays a dangling pointer
 *
 * The correct version on the right:
 *
 *   void free_list( list_ptr *list ){
 *       node_ptr p = *list;
 *       if( p ){
 *           *list = p->link;
 *           free(p);
 *           free_list(list);
 *   }}
 *
 * The step-by-step version below is the same as this one. */
void free_list(node_ptr *list) {
    node_ptr p = *list;
    if (p) {
        *list = p->link;      // first advance the head
        free(p);             // then free the old head
        free_list(list); // same address again
    }
}

void clear_list(node_ptr *list) {
    while (*list != NULL) {
        node_ptr p = *list;
        *list = p->link;     // advance first
        free(p);            // then free
    }
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

int main(void)
{
    int a[] = {4, 9};
    int b[] = {10, 20, 30};
    node_ptr list = build_list(a, 2);
    print_list(list);
    free_list(&list);
    printf("after free_list the list %s NULL\n", list == NULL ? "==" : "!=");

    list = build_list(b, 3);
    print_list(list);
    clear_list(&list);
    printf("after clear_list the list %s NULL\n", list == NULL ? "==" : "!=");
    return 0;
}

/* Note: the number lines end with a space. */
/* Expected output:
 * 4 9
 * after free_list the list == NULL
 * 10 20 30
 * after clear_list the list == NULL
 */
