/* Shared lists and reference counting: every list starts with a header
 * node, and the header keeps the number of pointers that point to the list
 * (ref). Example: A = (a,(b,c)), B = (A, A, ()). The ref of A is 3 (the
 * variable A and the two items of B). list_free(&B) does not free A, it
 * only lowers its ref to 1; list_free(&A) frees A.
 * Slides: "Shared Lists and Reference Counting", "Reference Counting Step by Step". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

/* not on the slides: node structure with a ref field in the header node */
typedef enum { FALSE, TRUE } boolean;
typedef struct list_node *list_pointer;
struct list_node {
    boolean tag;          // FALSE: atom
    union {
        char data;        // atom value
        list_pointer dlink; // sublist header
    };
    list_pointer link;    // next on this level
    int ref;              // header only: number of pointers to it
};

// header ref: how many pointers point to this list
void list_free(list_pointer *L) {
    list_pointer p, q;
    if (*L == NULL) return;
    if (--(*L)->ref > 0) {      // still in use
        *L = NULL; return;
    }
    p = (*L)->link;             // first real node
    free(*L);
    while (p) {
        if (p->tag) list_free(&p->dlink);
        q = p; p = p->link; free(q);
    }
    *L = NULL;
}

/* not on the slides: helpers that build and print nodes */
static list_pointer new_node(boolean tag, list_pointer link)
{
    list_pointer p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    p->tag = tag;
    p->link = link;
    p->ref = 0;
    return p;
}

static list_pointer header(int ref, list_pointer first)
{
    list_pointer h = new_node(FALSE, first);
    h->data = '#';
    h->ref = ref;
    return h;
}

static list_pointer atom(char c, list_pointer link)
{
    list_pointer p = new_node(FALSE, link);
    p->data = c;
    return p;
}

static list_pointer sub(list_pointer list, list_pointer link)  /* list: a header */
{
    list_pointer p = new_node(TRUE, link);
    p->dlink = list;
    return p;
}

static void print_header_list(list_pointer h)   /* prints a list with header */
{
    printf("(");
    for (list_pointer p = h->link; p; p = p->link) {
        if (p->tag) print_header_list(p->dlink);
        else printf("%c", p->data);
        if (p->link) printf(",");
    }
    printf(")");
}

int main(void)
{
    list_pointer A, B, bc, empty;

    bc = header(1, atom('b', atom('c', NULL)));
    A = header(1, atom('a', sub(bc, NULL)));
    empty = header(1, NULL);
    B = header(1, sub(A, sub(A, sub(empty, NULL))));
    A->ref += 2;                        /* both items of B point to A */

    printf("A = ");
    print_header_list(A);
    printf(", ref = %d\n", A->ref);
    printf("B = ");
    print_header_list(B);
    printf(", ref = %d\n", B->ref);

    list_free(&B);
    printf("list_free(&B): B is %s, ref of A = %d\n",
           B == NULL ? "NULL" : "not NULL", A->ref);
    list_free(&A);
    printf("list_free(&A): A is %s\n", A == NULL ? "NULL" : "not NULL");
    return 0;
}

/* Expected output:
 * A = (a,(b,c)), ref = 3
 * B = ((a,(b,c)),(a,(b,c)),()), ref = 1
 * list_free(&B): B is NULL, ref of A = 1
 * list_free(&A): A is NULL
 */
