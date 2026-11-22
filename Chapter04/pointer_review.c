/* Pointer refresher: changing an int through a pointer, allocating a single
 * node with malloc, filling it with ->, and releasing it with free.
 * Slides: "A Pointer Refresher", "A Node: A Self-Referential struct". */
#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ptr;  // pointer type first

struct node {
    int data;       // data field
    node_ptr link;    // address of the next node
};

int main(void)
{
    node_ptr list = NULL;  // empty list
    int x = 5;
    int *p = &x;       // p holds the address of x
    *p = 7;            // write through p: x == 7
    printf("x = %d\n", x);                         /* not on the slides */

    node_ptr q = NULL; // no node yet
    q = malloc(sizeof *q);
    if (q != NULL) {
        q->data = 3;  // (*q).data = 3
        q->link = NULL;
        printf("q->data = %d, (*q).data = %d, q->link %s NULL\n",  /* not on the slides */
               q->data, (*q).data, q->link == NULL ? "==" : "!=");
    }
    free(q);           // released; q now dangles
    q = NULL;
    printf("list %s NULL, q %s NULL\n",           /* not on the slides */
           list == NULL ? "==" : "!=", q == NULL ? "==" : "!=");
    return 0;
}

/* Expected output:
 * x = 7
 * q->data = 3, (*q).data = 3, q->link == NULL
 * list == NULL, q == NULL
 */
