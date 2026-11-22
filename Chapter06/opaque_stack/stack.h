/* stack.h: the opaque stack interface. The client does not see the fields of
 * struct Stack, it only works through a pointer.
 * Slide: "Better Design: The Stack as an Object" (block 1). */
/* stack.h: all the client sees */
#ifndef STACK_H
#define STACK_H
#include <stdbool.h>
typedef struct Stack Stack;  /* opaque */
Stack *stack_create(int capacity);
void stack_destroy(Stack *s);
bool push(Stack *s, int x);
bool pop(Stack *s, int *x);
bool stack_empty(const Stack *s);
#endif
