/* Queue as a linked list: items are added at the rear and removed at the
 * front; both are O(1). When the first item is added to an empty queue,
 * front changes too; when the last item is removed, rear is set to NULL
 * (otherwise a dangling pointer remains).
 * Examples from the notes: 10, 20, 30 are added to an empty queue; three
 * dequeue calls on the queue 10 -> 20 (the third returns false).
 * Slides: "Code Trace: Linked enqueue", "Code Trace: Linked dequeue". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: node type (from the notes) */
typedef struct node { int data; struct node *link; } node;

bool enqueue(node **front, node **rear, int x) {
  node *new_node = malloc(sizeof *new_node);
  if (new_node == NULL) return false;
  new_node->data = x;  new_node->link = NULL;
  if (*rear == NULL) *front = new_node; /* empty queue */
  else (*rear)->link = new_node;     /* link at end */
  *rear = new_node;
  return true;
}

bool dequeue(node **front, node **rear, int *x) {
  node *old = *front;
  if (old == NULL) return false;        /* empty */
  *x = old->data;
  *front = old->link;
  if (*front == NULL) *rear = NULL; /* last one gone */
  free(old);
  return true;
}

/* not on the slides: prints the queue from front to rear */
static void show(const node *front, const node *rear) {
  printf("queue:");
  for (; front != NULL; front = front->link) printf(" %d", front->data);
  if (rear != NULL) printf(" (rear = %d)\n", rear->data);
  else printf(" (rear = NULL)\n");
}

int main(void)
{
  node *front = NULL, *rear = NULL;
  int x;
  enqueue(&front, &rear, 10);
  show(front, rear);
  enqueue(&front, &rear, 20);
  enqueue(&front, &rear, 30);
  show(front, rear);
  dequeue(&front, &rear, &x);
  printf("dequeue: %d\n", x);
  show(front, rear);

  /* three dequeues on the remaining 20 -> 30; the second takes the last item */
  for (int i = 0; i < 3; i++) {
    if (dequeue(&front, &rear, &x)) printf("dequeue: true, %d\n", x);
    else printf("dequeue: false (empty)\n");
    show(front, rear);
  }
  enqueue(&front, &rear, 40);           /* adding to a queue that became empty */
  show(front, rear);
  dequeue(&front, &rear, &x);           /* not on the slides: release the memory */
  return 0;
}

/* Expected output:
 * queue: 10 (rear = 10)
 * queue: 10 20 30 (rear = 30)
 * dequeue: 10
 * queue: 20 30 (rear = 30)
 * dequeue: true, 20
 * queue: 30 (rear = 30)
 * dequeue: true, 30
 * queue: (rear = NULL)
 * dequeue: false (empty)
 * queue: (rear = NULL)
 * queue: 40 (rear = 40)
 */
