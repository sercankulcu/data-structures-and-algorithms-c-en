/* Stack on a global array: top is a local variable of the caller and is passed
 * by address. push first increments top, then stores (stack[++*top]); pop first
 * reads, then decrements (stack[(*top)--]). On a full or empty stack a warning
 * is printed and the program exits.
 * Trace from the notes: A, B, C are pushed, one item is popped, then D and E
 * are pushed. (In the notes, with MAX_STACK_SIZE = 4, pushing F ends the
 * program with "Stack is full!!!"; that step is not run here.)
 * Slides: "Array-Based Stack: C Definitions", "Push and Pop Routines", "Code
 * Trace: Array-Based Stack". */
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 101

typedef struct {
    int key;
    /* other fields */
} element;

element stack[MAX_STACK_SIZE];

void stack_full(void) {
    printf("Stack is full!!!\n"); exit(-1);
}
void stack_empty(void) {
    printf("Stack is empty!!!\n"); exit(-2);
}

void push(int *top, element item) {
    if (*top >= MAX_STACK_SIZE - 1)  /* any room? */
        stack_full();         /* warn and exit */
    stack[++*top] = item;     /* bump the index first */
}                             /* then store the item */

element pop(int *top) {
    if (*top < 0)
        stack_empty();          /* warn and exit if empty */
    return stack[(*top)--];   /* return, then decrement */
}

/* not on the slides: prints top and stack[0..top] */
static void show_state(int top) {
    printf("top = %d, stack:", top);
    for (int i = 0; i <= top; i++) printf(" %c", stack[i].key);
    printf("\n");
}

int main(void)
{
    int top = -1;                    /* empty stack */
    element e;
    char letters[] = "ABC";
    printf("start: ");
    show_state(top);
    for (int i = 0; i < 3; i++) {
        e.key = letters[i];
        push(&top, e);
        printf("push %c: ", letters[i]);
        show_state(top);
    }
    e = pop(&top);
    printf("pop -> %c: ", e.key);
    show_state(top);
    e.key = 'D'; push(&top, e);
    printf("push D: ");
    show_state(top);
    e.key = 'E'; push(&top, e);
    printf("push E: ");
    show_state(top);
    while (top >= 0) {               /* not on the slides: empty the stack */
        e = pop(&top);
        printf("pop -> %c\n", e.key);
    }
    return 0;
}

/* Expected output:
 * start: top = -1, stack:
 * push A: top = 0, stack: A
 * push B: top = 1, stack: A B
 * push C: top = 2, stack: A B C
 * pop -> C: top = 1, stack: A B
 * push D: top = 2, stack: A B D
 * push E: top = 3, stack: A B D E
 * pop -> E
 * pop -> D
 * pop -> B
 * pop -> A
 */
