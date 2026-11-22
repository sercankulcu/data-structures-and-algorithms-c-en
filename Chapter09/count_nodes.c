/* Exam question: the list node structure gets an extra int field count.
 * count_nodes stores the number of nodes under a sublist node into that
 * node's count and returns the total number of nodes. The counts are
 * printed in preorder (root first).
 * Slides: "Exam Question" (count_nodes and the linear form). */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

typedef enum { FALSE, TRUE } boolean;
typedef struct list_node *list_pointer;
struct list_node {
    boolean tag;          // FALSE: atom
    union {
        char data;        // atom value
        list_pointer dlink; // sublist head
    };
    list_pointer link;    // next on this level
    int count;            /* the extra field in the question text */
};

/* not on the slides: helper that allocates a node */
list_pointer get_node(void) {
    list_pointer p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "get_node: out of memory\n");
        exit(EXIT_FAILURE);
    }
    p->count = 0;
    return p;
}

/* not on the slides: reader that builds a list from the linear form (as in the lecture notes) */
list_pointer parse(const char **s) {
    list_pointer head = NULL, *last = &head, q;
    (*s)++;                             // skip '('
    while (**s != ')') {
        q = get_node();
        if (**s == '(') {               // sublist
            q->tag = TRUE;
            q->dlink = parse(s);
        } else {                        // atom
            q->tag = FALSE;
            q->data = **s;
            (*s)++;
        }
        q->link = NULL;
        *last = q;                      // link at the end
        last = &q->link;
        if (**s == ',') (*s)++;         // skip the separator
    }
    (*s)++;                             // skip ')'
    return head;
}

/* not on the slides: frees the list */
void list_clear(list_pointer L) {
    list_pointer q;
    while (L) {
        if (L->tag)
            list_clear(L->dlink);
        q = L;
        L = L->link;
        free(q);
    }
}

int count_nodes(list_pointer L) {
    int total = 0;              // an empty list has 0 nodes
    for (; L; L = L->link) {
        if (L->tag) {           // is there a sublist?
            L->count = count_nodes(L->dlink);
            total += L->count;  // count the sublist's nodes too
        }
        total++;                // the current node
    }
    return total;
}

void print_linear(list_pointer L) {
    printf("(");
    for (; L; L = L->link) {
        if (L->tag) print_linear(L->dlink);
        else printf("%c", L->data);
        if (L->link) printf(",");
    }
    printf(")");
}

/* not on the slides: prints the counts of the sublist nodes in preorder */
static void print_counts(list_pointer L)
{
    for (; L; L = L->link)
        if (L->tag) {
            printf(" %d", L->count);
            print_counts(L->dlink);
        }
}

int main(void)
{
    const char *lists[] = {
        "(a,(b,c))", "((a,b),((c,d),e))", "(())",
        "(d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,()))))",
    };
    list_pointer L;
    const char *s;
    int i, n;

    for (i = 0; i < 4; i++) {
        s = lists[i];
        L = parse(&s);
        n = count_nodes(L);
        print_linear(L);
        printf(" -> %d, counts:", n);
        print_counts(L);
        printf("\n");
        list_clear(L);
    }
    return 0;
}

/* Expected output:
 * (a,(b,c)) -> 4, counts: 2
 * ((a,b),((c,d),e)) -> 8, counts: 2 4 2
 * (()) -> 1, counts: 0
 * (d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,())))) -> 19, counts: 17 15 2 1 0 6 1 0
 */
