/* stack.c: the implementation of the opaque stack. The array is not fixed
 * inside the structure; stack_create allocates it from the heap with the
 * requested capacity.
 * Slide: "Better Design: The Stack as an Object" (block 2). push, pop and
 * stack_empty are not on the slide; they are written like push/pop in the
 * struct version. */
#include <stdlib.h>   /* not on the slides */
#include "stack.h"    /* not on the slides */

/* stack.c: implementation */
struct Stack { int *data; int top, cap; };

Stack *stack_create(int cap) {
  Stack *s = malloc(sizeof *s);
  if (s == NULL) return NULL;
  s->data = malloc(cap * sizeof *s->data);
  if (s->data == NULL) {
    free(s);  return NULL;
  }
  s->top = -1;  s->cap = cap;
  return s;
}
void stack_destroy(Stack *s) {
  if (s) { free(s->data); free(s); }
}

/* not on the slides */
bool push(Stack *s, int x) {
  if (s->top == s->cap - 1) return false;   /* tasma */
  s->data[++s->top] = x;
  return true;
}

/* not on the slides */
bool pop(Stack *s, int *x) {
  if (s->top < 0) return false;             /* alt tasma */
  *x = s->data[s->top--];
  return true;
}

/* not on the slides */
bool stack_empty(const Stack *s) { return s->top < 0; }
