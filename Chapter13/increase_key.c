/* An item whose priority changes: in a max heap, an item whose priority
 * rises is shifted up as long as it is larger than its parent (slide); an
 * item whose priority falls is shifted down (decrease_key in the notes).
 * Example from the notes (Example 13.3): in the heap 30, 15, 28, 11, 14, 3,
 * 6, 10, 9, increase_key(9, 31) and, from the same start, decrease_key(1, 5).
 * Slide: "Getting the Problem Right". */
#include <stdio.h>

/* not on the slides: the definitions of the "C definitions" slide */
#define MAX_ELEMENTS 200   /* max items + 1 */

typedef struct {
  int x;          /* priority (key) */
  /* other fields */
} element;

element heap[MAX_ELEMENTS];  /* [0] unused */
int n = 0;                   /* item count */

/* the priority of the item at position k rose: shift it up */
void increase_key(int k, int key) {
  element e = heap[k];
  e.x = key;
  while (k != 1 && e.x > heap[k / 2].x) {
    heap[k] = heap[k / 2];
    k /= 2;
  }
  heap[k] = e;
}

/* not on the slides: the shift-down version from the notes */
/* the priority of the item at position k fell: shift it down */
void decrease_key(int k, int key) {
  element e = heap[k];
  e.x = key;
  int j = 2 * k;
  while (j <= n) {
    if (j < n && heap[j].x < heap[j + 1].x) j++;
    if (e.x >= heap[j].x) break;
    heap[k] = heap[j];
    k = j; j *= 2;
  }
  heap[k] = e;
}

/* not on the slides: fills the heap with the given values */
static void fill(const int a[], int m) {
    for (int i = 0; i < m; i++)
        heap[i + 1].x = a[i];
    n = m;
}

/* not on the slides: prints heap[1..n] */
static void print_heap(void) {
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", heap[i].x);
    printf("\n");
}

int main(void)
{
    int a[] = {30, 15, 28, 11, 14, 3, 6, 10, 9};
    fill(a, 9);
    printf("start:                  ");
    print_heap();
    increase_key(9, 31);
    printf("increase_key(9, 31):    ");
    print_heap();

    fill(a, 9);
    decrease_key(1, 5);
    printf("decrease_key(1, 5):     ");
    print_heap();
    return 0;
}

/* Expected output:
 * start:                  30, 15, 28, 11, 14, 3, 6, 10, 9
 * increase_key(9, 31):    31, 30, 28, 15, 14, 3, 6, 10, 11
 * decrease_key(1, 5):     28, 15, 6, 11, 14, 3, 5, 10, 9
 */
