/* Bottom-up heap construction: from the last internal node (n/2) towards
 * the root, each node is sifted down; the total work is O(n).
 * Example from the notes (Table 13.14): 5, 3, 8, 9, 1, 12, 7 ->
 * 12, 9, 8, 3, 1, 5, 7.
 * Slides: "Bottom-up heap construction", "Trace: build_heap - 1",
 * "Trace: build_heap - 2". */
#include <stdio.h>

/* not on the slides: the item type of the "C definitions" slide */
typedef struct {
  int x;          /* priority (key) */
  /* other fields */
} element;

void build_heap(element a[], int n) {
  for (int k = n / 2; k >= 1; k--) {
    element temp = a[k];
    int i = k, j = 2 * k;
    while (j <= n) {
      if (j < n && a[j].x < a[j + 1].x) j++;
      if (temp.x >= a[j].x) break;
      a[i] = a[j];
      i = j; j *= 2;
    }
    a[i] = temp;
  }
}

/* not on the slides: prints a[1..n] */
static void print_array(const element a[], int n) {
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", a[i].x);
    printf("\n");
}

int main(void)
{
    /* a[0] is unused */
    element a[8] = {{0}, {5}, {3}, {8}, {9}, {1}, {12}, {7}};
    printf("input: ");
    print_array(a, 7);
    build_heap(a, 7);
    printf("heap:  ");
    print_array(a, 7);
    return 0;
}

/* Expected output:
 * input: 5, 3, 8, 9, 1, 12, 7
 * heap:  12, 9, 8, 3, 1, 5, 7
 */
