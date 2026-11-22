/* Double-ended queue (deque) in a circular array: push_front moves front
 * back by one ((front - 1 + CAP) % CAP, so there is no negative-remainder
 * trap), pop_back reads the last item from cell (front + count - 1) % CAP.
 * Example from the notes (Example 7.4): CAP = 5; push_back puts 10 and
 * 20, then push_front 5, push_front 3 and two pop_back calls; finally
 * pop_front.
 * Slide: "Code Trace: A Deque in a Circular Array". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: capacity (notes example) and deque type (from the notes) */
#define CAP 5
typedef struct { int data[CAP]; int front, count; } Deque;

bool push_front(Deque *d, int x) {
  if (d->count == CAP) return false;
  d->front = (d->front - 1 + CAP) % CAP;  /* one back */
  d->data[d->front] = x;  d->count++;
  return true;
}
bool pop_back(Deque *d, int *x) {
  if (d->count == 0) return false;
  *x = d->data[(d->front + d->count - 1) % CAP];
  d->count--;  return true;
}

/* not on the slides: push_back and pop_front from the notes */
bool push_back(Deque *d, int x) {
  if (d->count == CAP) return false;
  d->data[(d->front + d->count) % CAP] = x; /* one past the last item */
  d->count++;
  return true;
}
bool pop_front(Deque *d, int *x) {
  if (d->count == 0) return false;
  *x = d->data[d->front];
  d->front = (d->front + 1) % CAP;          /* one forward */
  d->count--;
  return true;
}

/* not on the slides: prints front, count and the logical order */
static void show(const char *op, const Deque *d) {
  printf("%s: front = %d, count = %d, order:", op, d->front, d->count);
  for (int i = 0; i < d->count; i++) printf(" %d", d->data[(d->front + i) % CAP]);
  printf("\n");
}

int main(void)
{
  Deque d = { {0}, 0, 0 };
  int x;
  push_back(&d, 10);
  push_back(&d, 20);
  show("start", &d);
  push_front(&d, 5);
  show("push_front 5", &d);
  push_front(&d, 3);
  show("push_front 3", &d);
  pop_back(&d, &x);
  printf("pop_back -> %d\n", x);
  show("pop_back", &d);
  pop_back(&d, &x);
  printf("pop_back -> %d\n", x);
  show("pop_back", &d);
  pop_front(&d, &x);
  printf("pop_front -> %d\n", x);
  show("pop_front", &d);
  return 0;
}

/* Expected output:
 * start: front = 0, count = 2, order: 10 20
 * push_front 5: front = 4, count = 3, order: 5 10 20
 * push_front 3: front = 3, count = 4, order: 3 5 10 20
 * pop_back -> 20
 * pop_back: front = 3, count = 3, order: 3 5 10
 * pop_back -> 10
 * pop_back: front = 3, count = 2, order: 3 5
 * pop_front -> 3
 * pop_front: front = 4, count = 1, order: 5
 */
