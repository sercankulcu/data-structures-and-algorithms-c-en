/* Circular queue: indices advance modulo MAX_QUEUE_SIZE and wrap around
 * at the end. front is one before the first item; front == rear means
 * empty, so one cell always stays unused. This version prints a warning
 * and exits when the queue is full or empty.
 * Example from the notes: six-cell queue, A..E are added, A is removed,
 * F is added; F is written to cell 0 by the wrap-around.
 * Slide: "Circular Queue: C Code". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: size (notes example), item type and error functions */
#define MAX_QUEUE_SIZE 6
typedef struct {
    int value;
} element;
element queue[MAX_QUEUE_SIZE];
void queue_full(void) {
    printf("Queue is full!!!\n"); exit(-1);
}
void queue_empty(void) {
    printf("Queue is empty!!!\n"); exit(-2);
}

void enqueue(int front, int *rear, element item) {
    *rear = (*rear + 1) % MAX_QUEUE_SIZE; /* advance */
    if (front == *rear) queue_full();     /* full? */
    queue[*rear] = item;                  /* store */
}
element dequeue(int *front, int rear) {
    if (*front == rear) queue_empty();    /* empty? */
    *front = (*front + 1) % MAX_QUEUE_SIZE; /* advance */
    return queue[*front];                 /* return */
}

/* not on the slides: prints the indices and the queue from front to rear */
static void show(int front, int rear) {
    printf("front = %d, rear = %d, queue:", front, rear);
    for (int i = front; i != rear; ) {
        i = (i + 1) % MAX_QUEUE_SIZE;
        printf(" %c@%d", queue[i].value, i);
    }
    printf("\n");
}

int main(void)
{
    int front = 0, rear = 0;           /* empty queue */
    element e;
    const char *letters = "ABCDE";
    show(front, rear);
    for (int i = 0; i < 5; i++) {
        e.value = letters[i];
        enqueue(front, &rear, e);
    }
    show(front, rear);
    e = dequeue(&front, rear);
    printf("dequeue -> %c\n", e.value);
    show(front, rear);
    e.value = 'F';
    enqueue(front, &rear, e);          /* rear 5 -> 0: wrap-around */
    show(front, rear);
    return 0;
}

/* Expected output:
 * front = 0, rear = 0, queue:
 * front = 0, rear = 5, queue: A@1 B@2 C@3 D@4 E@5
 * dequeue -> A
 * front = 1, rear = 5, queue: B@2 C@3 D@4 E@5
 * front = 1, rear = 0, queue: B@2 C@3 D@4 E@5 F@0
 */
