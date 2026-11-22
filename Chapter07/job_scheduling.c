/* Round-robin job scheduling simulation: process ids wait in a queue; the
 * process at the front runs for at most Q units and goes back to the end
 * if it still has work left. The queue is a counted circular queue.
 * Example from the notes: P0 = 5, P1 = 2, P2 = 4 units of work, Q = 2;
 * also the exercise in the notes with Q = 3.
 * Slide: "Code Trace: Round-Robin Scheduling". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: the counted queue from the notes */
#define CAP 16
typedef struct { int data[CAP]; int front, count; } Queue;
bool enqueue(Queue *q, int x) {
  if (q->count == CAP) return false;
  q->data[(q->front + q->count) % CAP] = x;
  q->count++;
  return true;
}
bool dequeue(Queue *q, int *x) {
  if (q->count == 0) return false;
  *x = q->data[q->front];
  q->front = (q->front + 1) % CAP;
  q->count--;
  return true;
}

/* not on the slides: runs the simulation with the given Q */
static void simulate(int Q) {
  int left[] = {5, 2, 4}; /* work left for P0, P1, P2 */
  int time = 0, p;
  Queue q = { {0}, 0, 0 }; /* empty counted queue */
  for (int i = 0; i < 3; i++)
    enqueue(&q, i); /* all start in the queue */
  printf("Q = %d\n", Q);

  /* q: queue of process ids; Q: time slice */
  while (dequeue(&q, &p)) {
    int run = left[p] < Q ? left[p] : Q;
    time += run;
    left[p] -= run;
    if (left[p] > 0)
      enqueue(&q, p);               /* back of line */
    else
      printf("P%d done: t=%d\n", p, time);
  }
}

int main(void)
{
  simulate(2);
  simulate(3);
  return 0;
}

/* Expected output:
 * Q = 2
 * P1 done: t=4
 * P2 done: t=10
 * P0 done: t=11
 * Q = 3
 * P1 done: t=5
 * P0 done: t=10
 * P2 done: t=11
 */
