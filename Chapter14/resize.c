/* Resizing: after every insertion into a dynamic table the load factor is
 * checked; when alpha > 1/2 the table grows to the first prime not smaller
 * than twice its size and every USED item is rehashed into the new table.
 * Example from the notes (Table 14.16): 7, 12, 3 are inserted into a table
 * with 5 slots; after 3, alpha = 0.6 and the table grows to 11 slots
 * (12 -> 1, 3 -> 3, 7 -> 7).
 * Slides: "Resizing", "Trace: resize". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* not on the slides: the slot type of the "Open addressing: C" slide */
typedef enum { EMPTY, USED, DELETED } state_t;
typedef struct {
  int key;              /* assumes key >= 0 */
  state_t state;
} slot;

typedef struct {
  slot *a;      /* dynamic array of m slots */
  int m, n;     /* size, number of used slots */
} Table;

/* not on the slides: two helpers (the versions in the notes) */
int next_prime(int x) {   /* the first prime not smaller than x */
  for (;; x++) {
    int prime = x >= 2;
    for (int d = 2; d * d <= x && prime; d++)
      if (x % d == 0) prime = 0;
    if (prime) return x;
  }
}
int table_insert(Table *t, int k) {   /* linear probing, m = t->m */
  int i = k % t->m;
  for (int d = 0; d < t->m; d++, i = (i + 1) % t->m) {
    if (t->a[i].state != USED) {
      t->a[i].key = k;
      t->a[i].state = USED;
      t->n++;
      return i;
    }
  }
  return -1;
}

bool resize(Table *t, int new_m) {
  slot *old = t->a;
  int old_m = t->m;
  slot *a = calloc(new_m, sizeof *a);  /* EMPTY */
  if (a == NULL) return false;
  t->a = a; t->m = new_m; t->n = 0;
  for (int i = 0; i < old_m; i++)
    if (old[i].state == USED)
      table_insert(t, old[i].key);
  free(old);
  return true;
}

/* not on the slides: prints the table; an empty slot is "." */
static void print_table(const Table *t) {
    printf("m = %d, n = %d:", t->m, t->n);
    for (int i = 0; i < t->m; i++) {
        if (t->a[i].state == USED) printf(" %d", t->a[i].key);
        else printf(" .");
    }
    printf("\n");
}

int main(void)
{
    Table table = {NULL, 5, 0}, *t = &table;
    t->a = calloc(t->m, sizeof *t->a);    /* not on the slides: the initial array */
    if (t->a == NULL) return 1;
    int k[] = {7, 12, 3};
    for (int i = 0; i < 3; i++) {
        table_insert(t, k[i]);
        printf("+%d: ", k[i]);
        print_table(t);
/* after inserting: */
if (2 * t->n > t->m)             /* α > 1/2 */
  resize(t, next_prime(2 * t->m));
    }
    printf("final: ");
    print_table(t);
    free(t->a);
    return 0;
}

/* Expected output:
 * +7: m = 5, n = 1: . . 7 . .
 * +12: m = 5, n = 2: . . 7 12 .
 * +3: m = 5, n = 3: . . 7 12 3
 * final: m = 11, n = 3: . 12 . 3 . . . 7 . . .
 */
