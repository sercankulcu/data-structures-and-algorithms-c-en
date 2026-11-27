/* Radix sort (radixsort, LSD): every item is a linked-list node holding its
 * three digits. For the ones, tens and hundreds digits in turn, the items are
 * distributed stably into ten buckets and the buckets are collected from 0 to
 * 9. The loop body from the slides is written as the function radixsort as in
 * the notes; build_list and free_list are from the notes. The example is
 * 179, 208, 306, 093, 859, 984, 055, 009, 271, 033 from the notes.
 * Slides: "Radix Sort", "Code Trace: ones pass", "Code Trace (Continued): i = 1
 * and i = 0". */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: malloc, free */

#define MAX_DIGIT 3
#define RADIX 10
typedef struct node *node_ptr;
struct node {
    int digit[MAX_DIGIT];  /* 179 -> {1, 7, 9} */
    node_ptr next;
};

/* not on the slides: function header and bucket arrays from the notes */
node_ptr radixsort(node_ptr p) {
    node_ptr head[RADIX], tail[RADIX];  /* bucket heads and tails */
    for (int i = MAX_DIGIT - 1; i >= 0; i--) {
        for (int j = 0; j < RADIX; j++)
            head[j] = tail[j] = NULL;
        for (; p; p = p->next) {     // distribute
            int b = p->digit[i];
            if (!head[b]) head[b] = p;
            else tail[b]->next = p;
            tail[b] = p;
        }
        for (int j = RADIX - 1; j >= 0; j--) // collect
            if (head[j]) { tail[j]->next = p; p = head[j]; }
    }
    return p;
}

void free_list(node_ptr *pp);   /* not on the slides: prototype */

/* not on the slides: from the notes */
/* builds a linked list from 3-digit numbers; on out-of-memory returns NULL after freeing what was built */
node_ptr build_list(const int x[], int n) {
    node_ptr head = NULL, last = NULL;
    for (int k = 0; k < n; k++) {
        node_ptr d = malloc(sizeof *d);
        if (d == NULL) {               /* stopped halfway: no leak */
            free_list(&head);
            return NULL;
        }
        d->digit[0] = x[k] / 100;      /* hundreds */
        d->digit[1] = x[k] / 10 % 10;  /* tens */
        d->digit[2] = x[k] % 10;       /* ones */
        d->next = NULL;
        if (last) last->next = d; else head = d;
        last = d;
    }
    return head;
}

/* not on the slides: from the notes */
/* frees all nodes of the list and sets the caller's pointer to NULL */
void free_list(node_ptr *pp) {
    while (*pp) {
        node_ptr next = (*pp)->next;
        free(*pp);
        *pp = next;
    }
}

/* not on the slides: prints the list with three digits */
static void print_list(const char *name, node_ptr p) {
    printf("%s", name);
    for (; p; p = p->next)
        printf(" %d%d%d", p->digit[0], p->digit[1], p->digit[2]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int x[] = {179, 208, 306, 93, 859, 984, 55, 9, 271, 33};
    node_ptr p = build_list(x, 10);
    if (p == NULL) return 1;
    print_list("before:", p);
    p = radixsort(p);
    print_list("after: ", p);
    free_list(&p);
    return 0;
}


/* Expected output:
 * before: 179 208 306 093 859 984 055 009 271 033
 * after:  009 033 055 093 179 208 271 306 859 984
 */
