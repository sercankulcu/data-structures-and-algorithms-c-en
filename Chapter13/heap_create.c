/* A struct instead of a global array: Heap holds the address of the array,
 * the item count and the capacity; the array is allocated at run time and
 * both allocations are checked.
 * Insertion and deletion are not in the slides; heap_insert / heap_pop from
 * the notes are used (success is reported with true/false).
 * Example from the notes: heap_create(4), an attempt to insert 20, 5, 30,
 * 10, 40 (the fifth fails with false because the heap is full), then removal
 * until empty.
 * Slide: "A Better Interface". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: the item type of the "C definitions" slide */
typedef struct {
  int x;          /* priority (key) */
  /* other fields */
} element;

typedef struct { element *a; int n, capacity; } Heap;

Heap *heap_create(int capacity) {
  Heap *h = malloc(sizeof *h);
  if (h == NULL) return NULL;
  h->a = malloc((capacity + 1) * sizeof *h->a);
  if (h->a == NULL) { free(h); return NULL; }
  h->n = 0; h->capacity = capacity;
  return h;
}
void heap_destroy(Heap *h) { if (h) { free(h->a); free(h); } }

/* not on the slides: insertion and deletion for the struct version (from the notes) */
bool heap_insert(Heap *h, element item) {
  if (h->n == h->capacity) return false;   /* full */
  int i = ++h->n;
  while (i != 1 && item.x > h->a[i / 2].x) {
    h->a[i] = h->a[i / 2];
    i /= 2;
  }
  h->a[i] = item;
  return true;
}
bool heap_pop(Heap *h, element *out) {
  if (h->n == 0) return false;             /* empty */
  *out = h->a[1];
  element temp = h->a[h->n--];
  int i = 1, j = 2;
  while (j <= h->n) {
    if (j < h->n && h->a[j].x < h->a[j + 1].x) j++;
    if (temp.x >= h->a[j].x) break;
    h->a[i] = h->a[j];
    i = j; j *= 2;
  }
  h->a[i] = temp;
  return true;
}

int main(void)
{
    Heap *h = heap_create(4);
    if (h == NULL) return 1;
    printf("capacity = %d, n = %d\n", h->capacity, h->n);
    int a[] = {20, 5, 30, 10, 40};
    for (int i = 0; i < 5; i++) {
        element e = {a[i]};
        printf("heap_insert(%d) = %s\n", a[i],
               heap_insert(h, e) ? "true" : "false");
    }
    element out;
    printf("popped:");
    while (heap_pop(h, &out))
        printf(" %d", out.x);
    printf("\n");
    heap_destroy(h);
    heap_destroy(NULL);       /* harmless */
    return 0;
}

/* Expected output:
 * capacity = 4, n = 0
 * heap_insert(20) = true
 * heap_insert(5) = true
 * heap_insert(30) = true
 * heap_insert(10) = true
 * heap_insert(40) = false
 * popped: 30 20 10 5
 */
