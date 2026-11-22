/* Open addressing, linear probing: insertion starts at the home address and
 * writes into the first EMPTY or DELETED slot; search stops at the first
 * EMPTY slot; erasure marks the slot DELETED so that the path to keys
 * further along is not cut.
 * Example from the notes: with M = 11, 22, 1, 13, 11, 24, 33 are inserted
 * (insert(33) goes to slot 5); search(24) = 4, search(44) = -1; after
 * erase(13), search(24) still finds 4.
 * Slides: "Open addressing: C", "Trace: insert(33)",
 * "Trace: search(24), search(44)", "Trace: erase(13), search(24)". */
#include <stdio.h>
#include <stdbool.h>

#define M 11
typedef enum { EMPTY, USED, DELETED } state_t;
typedef struct {
  int key;              /* assumes key >= 0 */
  state_t state;
} slot;
slot table[M];          /* global: all 0 = EMPTY */

int insert(int k) {
  int i = k % M;                 /* home address */
  for (int d = 0; d < M; d++, i = (i + 1) % M) {
    if (table[i].state != USED) {  /* EMPTY/DELETED */
      table[i].key = k;
      table[i].state = USED;
      return i;
    }
  }
  return -1;                     /* table full */
}

int search(int k) {
  int i = k % M;
  for (int d = 0; d < M; d++, i = (i + 1) % M) {
    if (table[i].state == EMPTY) return -1;
    if (table[i].state == USED &&
        table[i].key == k) return i;
  }
  return -1;
}
bool erase(int k) {
  int i = search(k);
  if (i < 0) return false;
  table[i].state = DELETED;   /* tombstone */
  return true;
}

/* not on the slides: prints the table; EMPTY ".", DELETED "x" */
static void print_table(void) {
    printf("table:");
    for (int i = 0; i < M; i++) {
        if (table[i].state == USED) printf(" %d", table[i].key);
        else if (table[i].state == EMPTY) printf(" .");
        else printf(" x");
    }
    printf("\n");
}

int main(void)
{
    int a[] = {22, 1, 13, 11, 24, 33};
    for (int i = 0; i < 6; i++)
        printf("insert(%d) = %d\n", a[i], insert(a[i]));
    print_table();
    printf("search(24) = %d\n", search(24));
    printf("search(44) = %d\n", search(44));
    printf("erase(13) = %d\n", erase(13));
    print_table();
    printf("search(24) = %d\n", search(24));
    printf("search(13) = %d\n", search(13));
    printf("erase(13) = %d\n", erase(13));
    return 0;
}

/* Expected output:
 * insert(22) = 0
 * insert(1) = 1
 * insert(13) = 2
 * insert(11) = 3
 * insert(24) = 4
 * insert(33) = 5
 * table: 22 1 13 11 24 33 . . . . .
 * search(24) = 4
 * search(44) = -1
 * erase(13) = 1
 * table: 22 1 x 11 24 33 . . . . .
 * search(24) = 4
 * search(13) = -1
 * erase(13) = 0
 */
