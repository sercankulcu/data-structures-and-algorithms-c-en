/* Max heap in an array: heap[1..n], the parent of i is i/2, its children are
 * 2i and 2i+1. Insertion shifts the hole up, deletion shifts the last item
 * down.
 * Examples from the notes: 15, 109, 107, 3, 15 are inserted into the heap
 * 14, 12, 7, 10, 8, 6 and two items are removed (Example 13.4); the heap
 * 30, 15, 28, 11, 14, 3, 6, 10, 9 is emptied by removals (Tables 13.6-13.8).
 * Slides: "C definitions", "Insert routine", "Trace: insert(15)",
 * "Trace: insert(109)", "Delete routine", "Trace: pop() - 1",
 * "Trace: pop() - 2". */
#include <stdio.h>
#include <stdbool.h>

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

void insert_max_heap(element item) {
  if (HEAP_FULL(n)) {
    heap_full();              /* error message */
    return;
  }
  int i = ++n;
  while (i != 1) {            /* i == 1: we are at the root */
    if (item.x <= heap[i / 2].x) break;
    heap[i] = heap[i / 2];    /* move the parent down */
    i /= 2;                   /* look at the next parent up */
  }
  heap[i] = item;
}

bool delete_max_heap(element *out) {
  if (HEAP_EMPTY(n)) return false;
  *out = heap[1];             /* the root is returned */
  element temp = heap[n--];   /* its slot is to be found */
  int i = 1, j = 2;
  while (j <= n) {
    if (j < n && heap[j].x < heap[j + 1].x) j++;
    if (temp.x >= heap[j].x) break;
    heap[i] = heap[j];        /* move the child up */
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
    int first[] = {14, 12, 7, 10, 8, 6};
    for (int i = 0; i < 6; i++) {
        element e = {first[i]};
        insert_max_heap(e);
    }
    printf("start: ");
    print_heap();

    int added[] = {15, 109, 107, 3, 15};
    for (int i = 0; i < 5; i++) {
        element e = {added[i]};
        insert_max_heap(e);
        printf("+%d: ", added[i]);
        print_heap();
    }
    element out;
    for (int i = 0; i < 2; i++) {
        delete_max_heap(&out);
        printf("pop %d: ", out.x);
        print_heap();
    }

    n = 0;                    /* second example: rebuild the heap */
    int second[] = {30, 15, 28, 11, 14, 3, 6, 10, 9};
    for (int i = 0; i < 9; i++) {
        element e = {second[i]};
        insert_max_heap(e);
    }
    printf("start: ");
    print_heap();
    while (delete_max_heap(&out)) {
        printf("pop %d: ", out.x);
        print_heap();
    }
    printf("pop from an empty heap: %s\n",
           delete_max_heap(&out) ? "true" : "false");
    return 0;
}

/* Expected output:
 * start: 14, 12, 7, 10, 8, 6
 * +15: 15, 12, 14, 10, 8, 6, 7
 * +109: 109, 15, 14, 12, 8, 6, 7, 10
 * +107: 109, 107, 14, 15, 8, 6, 7, 10, 12
 * +3: 109, 107, 14, 15, 8, 6, 7, 10, 12, 3
 * +15: 109, 107, 14, 15, 15, 6, 7, 10, 12, 3, 8
 * pop 109: 107, 15, 14, 12, 15, 6, 7, 10, 8, 3
 * pop 107: 15, 15, 14, 12, 3, 6, 7, 10, 8
 * start: 30, 15, 28, 11, 14, 3, 6, 10, 9
 * pop 30: 28, 15, 9, 11, 14, 3, 6, 10
 * pop 28: 15, 14, 9, 11, 10, 3, 6
 * pop 15: 14, 11, 9, 6, 10, 3
 * pop 14: 11, 10, 9, 6, 3
 * pop 11: 10, 6, 9, 3
 * pop 10: 9, 6, 3
 * pop 9: 6, 3
 * pop 6: 3
 * pop 3: (empty)
 * pop from an empty heap: false
 */
