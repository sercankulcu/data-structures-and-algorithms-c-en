/* Counted circular queue: front is the first item itself, count is the
 * number of items; so all CAP cells are used. The new item is written to
 * cell (front + count) % CAP.
 * Example from the notes (Example 7.3): CAP = 3; 1, 2, 3, 4 are added
 * (4 is rejected), one item is removed, 4 is added (wrap-around), one more
 * item is removed.
 * Slide: "Code Trace: A Circular Queue with a Count". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: capacity (notes example) and queue type (from the notes) */
#define CAP 3
typedef struct { int data[CAP]; int front, count; } Queue;

bool enqueue(Queue *q, int x) {
  if (q->count == CAP) return false;       /* full */
  q->data[(q->front + q->count) % CAP] = x;
  q->count++;
  return true;
}
bool dequeue(Queue *q, int *x) {
  if (q->count == 0) return false;         /* empty */
  *x = q->data[q->front];
  q->front = (q->front + 1) % CAP;
  q->count--;
  return true;
}

/* not on the slides: prints the state and the logical order */
static void show(const Queue *q) {
  printf("  front = %d, count = %d, order:", q->front, q->count);
  for (int i = 0; i < q->count; i++) printf(" %d", q->data[(q->front + i) % CAP]);
  printf("\n");
}

int main(void)
{
  Queue q = { {0}, 0, 0 };
  int x;
  for (int i = 1; i <= 4; i++) {
    printf("enqueue %d: %s\n", i, enqueue(&q, i) ? "true" : "false (full)");
    show(&q);
  }
  if (dequeue(&q, &x)) printf("dequeue: %d\n", x);
  show(&q);
  printf("enqueue 4: %s\n", enqueue(&q, 4) ? "true" : "false (full)");
  show(&q);
  printf("data[0] = %d (wrap-around)\n", q.data[0]);
  if (dequeue(&q, &x)) printf("dequeue: %d\n", x);
  show(&q);
  return 0;
}

/* Expected output:
 * enqueue 1: true
 *   front = 0, count = 1, order: 1
 * enqueue 2: true
 *   front = 0, count = 2, order: 1 2
 * enqueue 3: true
 *   front = 0, count = 3, order: 1 2 3
 * enqueue 4: false (full)
 *   front = 0, count = 3, order: 1 2 3
 * dequeue: 1
 *   front = 1, count = 2, order: 2 3
 * enqueue 4: true
 *   front = 1, count = 3, order: 2 3 4
 * data[0] = 4 (wrap-around)
 * dequeue: 2
 *   front = 2, count = 2, order: 3 4
 */
