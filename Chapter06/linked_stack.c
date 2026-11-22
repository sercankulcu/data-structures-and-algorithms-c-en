/* Stack with a linked list: top is the head of the list. push links a new node
 * in front of the old top; pop first saves the value and the link, and frees
 * last; stack_clear returns the remaining nodes.
 * Examples from the notes: 10, 20, 30 are pushed onto an empty stack and four
 * pops are done; then push 10, 20, 30, pop, push 40 and stack_clear.
 * Slides: "Implementing a Stack with a Linked List", "Who Owns the Memory in a
 * Linked Stack". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *link;
} node;

void stack_clear(node **top) {
    while (*top != NULL) {
        node *old = *top;
        *top = old->link;
        free(old);
    }
}                  /* afterwards *top == NULL */

bool push(node **top, int x) {
  node *new_node = malloc(sizeof *new_node);
  if (new_node == NULL) return false;  /* no memory */
  new_node->data = x;
  new_node->link = *top;      /* point to old top */
  *top = new_node;           /* new top */
  return true;
}

bool pop(node **top, int *x) {
  node *old = *top;      /* no malloc! */
  if (old == NULL) return false;  /* empty */
  *x = old->data;
  *top = old->link;        /* advance top */
  free(old);              /* release memory */
  return true;
}

/* not on the slides: prints the stack from top to bottom */
static void print_stack(const node *top) {
    printf("stack:");
    for (; top != NULL; top = top->link) printf(" %d ->", top->data);
    printf(" NULL\n");
}

int main(void)
{
    node *top = NULL;
    int x, i;
    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    print_stack(top);
    for (i = 0; i < 4; i++) {
        if (pop(&top, &x)) printf("pop: true, %d\n", x);
        else printf("pop: false (empty)\n");
    }

    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    pop(&top, &x);
    push(&top, 40);
    print_stack(top);
    stack_clear(&top);
    printf("after stack_clear top %s NULL\n", top == NULL ? "==" : "!=");
    return 0;
}

/* Expected output:
 * stack: 30 -> 20 -> 10 -> NULL
 * pop: true, 30
 * pop: true, 20
 * pop: true, 10
 * pop: false (empty)
 * stack: 40 -> 20 -> 10 -> NULL
 * after stack_clear top == NULL
 */
