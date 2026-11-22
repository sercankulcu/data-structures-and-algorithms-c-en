/* Safe version of the circular queue: the new rear is computed in a local
 * variable first; if the queue is full, enqueue returns false without
 * changing rear, and dequeue returns false when the queue is empty. The
 * program does not exit.
 * Example from the notes (Example 7.2): five cells, front = rear = 0;
 * A..E are added (E is rejected), two items are removed, then E, F, G
 * are added (G is rejected).
 * Slide: "Code Trace: A Safe Circular Queue". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: size (notes example) and item type */
#define MAX_QUEUE_SIZE 5
typedef struct {
    int value;
} element;
element queue[MAX_QUEUE_SIZE];

bool enqueue(int front, int *rear, element x) {
  int next = (*rear + 1) % MAX_QUEUE_SIZE;
  if (next == front) return false;    /* full */
  *rear = next;  queue[next] = x;
  return true;
}
bool dequeue(int *front, int rear, element *x) {
  if (*front == rear) return false;   /* empty */
  *front = (*front + 1) % MAX_QUEUE_SIZE;
  *x = queue[*front];  return true;
}

/* not on the slides: performs one enqueue and prints the result */
static void add(int front, int *rear, char c) {
  element e;
  bool ok;
  e.value = c;
  ok = enqueue(front, rear, e);
  printf("enqueue %c: %s, front = %d, rear = %d\n", c,
         ok ? "true" : "false (full)", front, *rear);
}

int main(void)
{
  int front = 0, rear = 0;
  element e;
  const char *letters = "ABCDE";
  for (int i = 0; i < 5; i++) add(front, &rear, letters[i]);
  for (int i = 0; i < 2; i++)
    if (dequeue(&front, rear, &e))
      printf("dequeue: true, %c, front = %d, rear = %d\n", e.value, front, rear);
  add(front, &rear, 'E');
  add(front, &rear, 'F');
  add(front, &rear, 'G');
  while (dequeue(&front, rear, &e))      /* not on the slides: take the rest */
    printf("dequeue: %c\n", e.value);
  printf("dequeue: false (empty)\n");
  return 0;
}

/* Expected output:
 * enqueue A: true, front = 0, rear = 1
 * enqueue B: true, front = 0, rear = 2
 * enqueue C: true, front = 0, rear = 3
 * enqueue D: true, front = 0, rear = 4
 * enqueue E: false (full), front = 0, rear = 4
 * dequeue: true, A, front = 1, rear = 4
 * dequeue: true, B, front = 2, rear = 4
 * enqueue E: true, front = 2, rear = 0
 * enqueue F: true, front = 2, rear = 1
 * enqueue G: false (full), front = 2, rear = 1
 * dequeue: C
 * dequeue: D
 * dequeue: E
 * dequeue: F
 * dequeue: false (empty)
 */
