/* Using the opaque stack: client code sees only stack.h. 1, 2, 3, 4 are
 * pushed onto a stack of capacity 3 (4 is rejected), then the stack is emptied
 * and destroyed.
 * Slide: "Better Design: The Stack as an Object". This whole file is not on
 * the slides. */
#include <stdio.h>
#include "stack.h"

int main(void)
{
    Stack *s = stack_create(3);
    int x, i;
    if (s == NULL) return 1;
    for (i = 1; i <= 4; i++)
        printf("push %d: %s\n", i, push(s, i) ? "true" : "false");
    while (!stack_empty(s)) {
        pop(s, &x);
        printf("pop: %d\n", x);
    }
    printf("pop on an empty stack: %s\n", pop(s, &x) ? "true" : "false");
    stack_destroy(s);
    return 0;
}

/* Expected output:
 * push 1: true
 * push 2: true
 * push 3: true
 * push 4: false
 * pop: 3
 * pop: 2
 * pop: 1
 * pop on an empty stack: false
 */
