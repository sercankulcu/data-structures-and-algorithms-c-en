/* Linear queue in an array: front is one before the first item, rear is
 * the last item; both indices only move forward. enqueue takes rear and
 * dequeue takes front by address. A warning is printed and the program
 * exits when the queue is full or empty.
 * Trace from the notes: A, B, C are added; two items are removed; D is
 * added. In the notes, with MAX_QUEUE_SIZE = 4, adding E prints "Queue is
 * full!!!" although two cells are free (false fullness); that step is not
 * run here, the program only shows that front and rear always move forward.
 * Slides: "Linear Queue in an Array", "Code Trace: The Linear Queue and False Fullness". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: item type and error functions (from the notes) */
typedef struct {
    int value;
} element;
void queue_full(void) {
    printf("Queue is full!!!\n"); exit(-1);
}
void queue_empty(void) {
    printf("Queue is empty!!!\n"); exit(-2);
}

#define MAX_QUEUE_SIZE 100
element queue[MAX_QUEUE_SIZE];
int front = -1;     /* one before the first item */
int rear = -1;      /* last item */

void enqueue(int *rear, element item) {
    if (*rear >= MAX_QUEUE_SIZE - 1)   /* any room? */
        queue_full();          /* warn and exit */
    queue[++*rear] = item;     /* bump, then store */
}
element dequeue(int *front, int rear) {
    if (*front == rear)
        queue_empty();         /* warn and exit if empty */
    return queue[++*front];    /* bump, return the front */
}

/* not on the slides: prints the indices and the queue (front+1 .. rear) */
static void show(void) {
    printf("front = %d, rear = %d, queue:", front, rear);
    for (int i = front + 1; i <= rear; i++) printf(" %c", queue[i].value);
    printf("\n");
}

int main(void)
{
    element e;
    const char *letters = "ABC";
    show();
    for (int i = 0; i < 3; i++) {
        e.value = letters[i];
        enqueue(&rear, e);
    }
    show();
    e = dequeue(&front, rear);
    printf("dequeue -> %c\n", e.value);
    e = dequeue(&front, rear);
    printf("dequeue -> %c\n", e.value);
    show();
    e.value = 'D';
    enqueue(&rear, e);
    show();
    printf("cells 0..%d can no longer be used, room left: %d\n",
           front, MAX_QUEUE_SIZE - 1 - rear);
    return 0;
}

/* Expected output:
 * front = -1, rear = -1, queue:
 * front = -1, rear = 2, queue: A B C
 * dequeue -> A
 * dequeue -> B
 * front = 1, rear = 2, queue: C
 * front = 1, rear = 3, queue: C D
 * cells 0..1 can no longer be used, room left: 96
 */
