/* Queue with two stacks: enqueue always pushes onto the in stack; dequeue,
 * if the out stack is empty, moves everything from in to out (the order is
 * reversed twice) and then pops from out.
 * Example from the notes: enqueue 1, 2, 3; dequeue; enqueue 4; dequeue
 * three times; dequeue from the empty queue.
 * Slide: "Code Trace: A Queue Built from Two Stacks". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: the struct stack from Chapter 6 and the Queue2 type
 * (from the notes) */
#define CAP 100
typedef struct {
    int data[CAP];
    int top;               /* -1 when empty */
} Stack;
bool stack_empty(const Stack *s) { return s->top < 0; }
bool push(Stack *s, int x) {
  if (s->top == CAP - 1) return false;
  s->data[++s->top] = x;
  return true;
}
bool pop(Stack *s, int *x) {
  if (s->top < 0) return false;
  *x = s->data[s->top--];
  return true;
}
typedef struct { Stack in, out; } Queue2;

void enqueue(Queue2 *q, int x) {
  push(&q->in, x);
}
bool dequeue(Queue2 *q, int *x) {
  int t;
  if (stack_empty(&q->out))      /* out is empty */
    while (pop(&q->in, &t))      /* move them all */
      push(&q->out, t);
  return pop(&q->out, x);
}

/* not on the slides: does one dequeue, prints the result and the stack sizes */
static void dequeue_show(Queue2 *q) {
  int x;
  if (dequeue(q, &x)) printf("dequeue -> %d", x);
  else printf("dequeue -> false (empty)");
  printf("  in %d items, out %d items\n", q->in.top + 1, q->out.top + 1);
}

int main(void)
{
  Queue2 q;
  q.in.top = -1;
  q.out.top = -1;
  enqueue(&q, 1);
  enqueue(&q, 2);
  enqueue(&q, 3);
  dequeue_show(&q);        /* 3, 2, 1 are moved over */
  enqueue(&q, 4);
  dequeue_show(&q);        /* no move */
  dequeue_show(&q);
  dequeue_show(&q);        /* 4 is moved over */
  dequeue_show(&q);
  return 0;
}

/* Expected output:
 * dequeue -> 1  in 0 items, out 2 items
 * dequeue -> 2  in 1 items, out 1 items
 * dequeue -> 3  in 1 items, out 0 items
 * dequeue -> 4  in 0 items, out 0 items
 * dequeue -> false (empty)  in 0 items, out 0 items
 */
