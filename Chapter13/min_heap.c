/* Min heap: only the direction of the comparisons changes compared with the
 * max heap routines. Insertion is from the slides, deletion from the notes
 * (13.5.2).
 * Example from the notes: 20, 5, 30, 10, 40 are inserted into an empty
 * heap, then removed until it is empty; the items come out in ascending
 * order.
 * Slide: "Min heap". */
#include <stdio.h>
#include <stdbool.h>

/* not on the slides: the definitions of the "C definitions" slide */
#define MAX_ELEMENTS 200   /* max items + 1 */
#define HEAP_FULL(n) ((n) == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n)  (!(n))

typedef struct {
  int x;          /* priority (key) */
  /* other fields */
} element;

element heap[MAX_ELEMENTS];  /* [0] unused */
int n = 0;                   /* item count */

/* not on the slides: error message for a full heap */
void heap_full(void) {
    fprintf(stderr, "Heap is full\n");
}

void insert_min_heap(element item) {
  /* ... the full check is the same ... */
  if (HEAP_FULL(n)) {         /* not on the slides: the omitted full check */
    heap_full();
    return;
  }
  int i = ++n;
  while (i != 1) {
    if (item.x >= heap[i / 2].x) break; /* >= ! */
    heap[i] = heap[i / 2];
    i /= 2;
  }
  heap[i] = item;
}

/* not on the slides: deletion from a min heap (the version in the notes) */
bool delete_min_heap(element *out) {
  if (HEAP_EMPTY(n)) return false;
  *out = heap[1];
  element temp = heap[n--];
  int i = 1, j = 2;
  while (j <= n) {
    if (j < n && heap[j].x > heap[j + 1].x) j++;  /* the smaller child */
    if (temp.x <= heap[j].x) break;               /* <= ! */
    heap[i] = heap[j];
    i = j; j *= 2;
  }
  heap[i] = temp;
  return true;
}

/* not on the slides: prints heap[1..n] */
static void print_heap(void) {
    if (n == 0) printf("(empty)");
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", heap[i].x);
    printf("\n");
}

int main(void)
{
    int a[] = {20, 5, 30, 10, 40};
    for (int i = 0; i < 5; i++) {
        element e = {a[i]};
        insert_min_heap(e);
        printf("+%d: ", a[i]);
        print_heap();
    }
    element out;
    while (delete_min_heap(&out)) {
        printf("pop %d: ", out.x);
        print_heap();
    }
    return 0;
}

/* Expected output:
 * +20: 20
 * +5: 5, 20
 * +30: 5, 20, 30
 * +10: 5, 10, 30, 20
 * +40: 5, 10, 30, 20, 40
 * pop 5: 10, 20, 30, 40
 * pop 10: 20, 40, 30
 * pop 20: 30, 40
 * pop 30: 40
 * pop 40: (empty)
 */
