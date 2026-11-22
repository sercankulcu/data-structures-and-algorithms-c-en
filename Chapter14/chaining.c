/* Separate chaining: each bucket is the head of a linked list; insertion is
 * at the head, search walks only the chain of its own bucket, and erasure
 * keeps a previous pointer (the bucket is updated for the head node).
 * Example from the notes: MZ = 5, 10 and 4 are inserted, then 12, 7, 22
 * (all in bucket 2, chain 22 -> 7 -> 12); chain_search(12) and (17);
 * chain_erase(7), a second chain_erase(7), and the erasure of the head 22.
 * Slides: "Chaining" (two slides), "Trace: chain_insert",
 * "Trace: chain_search", "Trace: chain_erase". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MZ 5
typedef struct node {
  int key;
  struct node *next;
} node;
node *bucket[MZ];          /* all NULL */

bool chain_insert(int k) {
  int i = k % MZ;
  node *np = malloc(sizeof *np);
  if (np == NULL) return false;  /* no memory */
  np->key = k;
  np->next = bucket[i];          /* at the head */
  bucket[i] = np;
  return true;
}

node *chain_search(int k) {
  node *p = bucket[k % MZ];
  while (p != NULL && p->key != k)
    p = p->next;
  return p;                 /* NULL: absent */
}

bool chain_erase(int k) {
  int i = k % MZ;
  node *p = bucket[i], *prev = NULL;
  while (p != NULL && p->key != k) {
    prev = p;
    p = p->next;
  }
  if (p == NULL) return false;           /* absent */
  if (prev == NULL) bucket[i] = p->next;
  else prev->next = p->next;
  free(p);
  return true;
}

/* not on the slides: returns all memory of the table (from the notes) */
void chain_clear(void) {
  for (int i = 0; i < MZ; i++) {
    node *p = bucket[i];
    while (p != NULL) {
      node *next = p->next;   /* save it before free */
      free(p);
      p = next;
    }
    bucket[i] = NULL;
  }
}

/* not on the slides: prints the buckets */
static void print_table(void) {
    for (int i = 0; i < MZ; i++) {
        printf("bucket %d:", i);
        for (node *p = bucket[i]; p != NULL; p = p->next)
            printf(" %d", p->key);
        printf("\n");
    }
}

int main(void)
{
    int a[] = {10, 4, 12, 7, 22};
    for (int i = 0; i < 5; i++)
        chain_insert(a[i]);
    print_table();
    printf("chain_search(12): %s\n", chain_search(12) ? "found" : "absent");
    printf("chain_search(17): %s\n", chain_search(17) ? "found" : "absent");
    printf("chain_erase(7) = %d\n", chain_erase(7));
    printf("chain_erase(7) = %d\n", chain_erase(7));
    printf("chain_erase(22) = %d\n", chain_erase(22));
    print_table();
    chain_clear();
    return 0;
}

/* Expected output:
 * bucket 0: 10
 * bucket 1:
 * bucket 2: 22 7 12
 * bucket 3:
 * bucket 4: 4
 * chain_search(12): found
 * chain_search(17): absent
 * chain_erase(7) = 1
 * chain_erase(7) = 0
 * chain_erase(22) = 1
 * bucket 0: 10
 * bucket 1:
 * bucket 2: 12
 * bucket 3:
 * bucket 4: 4
 */
