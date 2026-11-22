/* Generalized lists: node structure with an atom/sublist tag and the basic
 * recursive routines. Lists are read from the linear form (for example
 * "(a,(b,c))") and written back with print_linear. Shown: copy, equal,
 * same, print_atoms, depth (recursive), iter_depth (with a local stack),
 * invert (reverses every level), print_tree (tree notation).
 * Slides: "Node Structure and Memory Layout", "QUESTION: copy a List with No Sharing
 * and No Recursion", "Code Trace: copy(L)", "QUESTION: Are Two Lists equal?",
 * "Code Trace: equal(T, L)", "A Better Version, and Shared Lists",
 * "QUESTION: Traverse the List and print Its Atoms", "Code Trace: print_atoms(L)",
 * "QUESTION: The depth of a List, Recursively", "Code Trace: depth(L)",
 * "QUESTION: depth, Iteratively (a Student Solution)", "Iterative depth with a
 * Local Stack", "QUESTION: invert an Unshared List", "Code Trace: invert(&L)",
 * "Assignments", "Exam Question". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */
#include <stdbool.h>  /* not on the slides: bool for same */

typedef enum { FALSE, TRUE } boolean;
typedef struct list_node *list_pointer;
struct list_node {
    boolean tag;          // FALSE: atom
    union {
        char data;        // atom value
        list_pointer dlink; // sublist head
    };
    list_pointer link;    // next on this level
};

/* not on the slides: helper that allocates a node (as in the lecture notes) */
list_pointer get_node(void) {
    list_pointer p = malloc(sizeof *p);
    if (p == NULL) {                    // out of memory
        fprintf(stderr, "get_node: out of memory\n");
        exit(EXIT_FAILURE);
    }
    return p;                           // fields are not initialized
}

/* not on the slides: reader that builds a list from the linear form (as in the lecture notes) */
// called while *s points at '('; when the list is built,
// *s points one past the matching ')'.
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

/* not on the slides: frees an unshared list (as in the lecture notes) */
void list_clear(list_pointer L) {
    list_pointer q;
    while (L) {
        if (L->tag)
            list_clear(L->dlink);       // the sublist first
        q = L;
        L = L->link;                    // read link before free
        free(q);
    }
}

/* "Exam Question": the linear form */
void print_linear(list_pointer L) {
    printf("(");
    for (; L; L = L->link) {
        if (L->tag) print_linear(L->dlink);
        else printf("%c", L->data);
        if (L->link) printf(",");
    }
    printf(")");
}

/* "QUESTION: copy a List" */
list_pointer copy(list_pointer L) {
    list_pointer q = NULL;
    if (L) {                    // L not NULL?
        q = get_node();         // get a node
        q->tag = L->tag;
        if (!L->tag) q->data = L->data; // atom
        else q->dlink = copy(L->dlink);
        q->link = copy(L->link);
    }
    return q;
}

/* "QUESTION: Are Two Lists equal?" */
boolean equal(list_pointer T, list_pointer L) {
    boolean x = TRUE;
    if (!T && !L) return TRUE;
    if (T && L && T->tag == L->tag) {
        if (!T->tag)             // atoms?
            x = (T->data == L->data) ? TRUE : FALSE;
        else                    // sublists
            x = equal(T->dlink, L->dlink);
        if (x == TRUE) return equal(T->link, L->link);
    }
    return FALSE;
}

/* "A Better Version, and Shared Lists" */
bool same(list_pointer T, list_pointer L) {
    if (T == L) return true;        // same node/both NULL
    if (!T || !L || T->tag != L->tag) return false;
    if (T->tag ? !same(T->dlink, L->dlink)
               : T->data != L->data)
        return false;
    return same(T->link, L->link);
}

/* The first version on the "QUESTION: Traverse the List and print Its Atoms" slide is wrong and
 * is not run: the calls refer to an undefined function print (it does not
 * compile), and since there are no braces after if (L), the last line also
 * runs when L == NULL.
 *
 * void print_atoms( list_pointer L ){
 *     if(L)
 *         if(!L->tag)
 *             printf("%c", L->data);
 *         else
 *             print(L->dlink);
 *         print( L->link );
 * }
 *
 * The correct version: */
void print_atoms(list_pointer L) {
    if (L) {
        if (!L->tag)
            printf("%c", L->data); // print an atom
        else
            print_atoms(L->dlink);
        print_atoms(L->link);
    }
}

/* "QUESTION: The depth of a List, Recursively" */
int depth(list_pointer L) {
    list_pointer p = L;  int m = 0; // m: the max
    if (!L) return 0;
    while (p) {
        if (p->tag) {
            int n = depth(p->dlink);
            if (m < n) m = n;
        }
        p = p->link;
    }
    return m + 1;
}

/* The student answer on the "QUESTION: depth, Iteratively" slide is wrong and
 * does not compile (p is declared as an int, the third part of the for
 * does not advance p, it relies on a global stack); as a comment only:
 *
 * int depth( tree_pointer L ){
 *     tree_pointer pop(); void push(tree_pointer);
 *     int max = 0;
 *     for( int current = 1, p = L ; p ; p->link ){
 *         if( p->tag ){ // enter the sublist
 *             push(p);
 *             p = p -> dlink;
 *             current++;
 *         }
 *         if( !p->link ){   // end of list, go up
 *             p = pop();
 *             if( max < current ) max = current;
 *             current--;
 *         }
 *     }
 *     return max;
 * }
 *
 * "Iterative depth with a Local Stack": */
int iter_depth(list_pointer L) {
    list_pointer stack[100];   // local stack (depth<100)
    int top = 0, d = 1, m = 0;
    list_pointer p = L;
    if (!L) return 0;
    for (;;) {
        if (p == NULL) {             // level done
            if (top == 0) return m;
            p = stack[--top]->link;  // the node after T
            d--;
        } else {
            if (d > m) m = d;
            if (p->tag && p->dlink) {
                stack[top++] = p;    // descend
                p = p->dlink;
                d++;
            } else p = p->link;
        }
    }
}

/* "QUESTION: invert an Unshared List" */
void invert(list_pointer *L) {
    list_pointer r, p = *L, q = NULL;
    while (p) {
        if (p->tag)                 // not an atom
            invert(&p->dlink);
        r = q;
        q = p;
        p = p->link;
        q->link = r;
    }
    *L = q;
}

/* "Assignments" */
void print_tree(list_pointer L) {   // L: (root, subtrees...)
    printf("%c", L->data);          // root label
    if (L->link) {
        printf("(");
        for (list_pointer p = L->link; p; p = p->link) {
            if (p->tag) print_tree(p->dlink);
            else printf("%c", p->data);   // leaf
            if (p->link) printf(",");
        }
        printf(")");
    }
}

/* not on the slides: builds a list from a string */
static list_pointer read_list(const char *text)
{
    const char *s = text;
    return parse(&s);
}

int main(void)
{
    const char *deep[] = {
        "(a,b)", "(a,(b,c))", "(a,(b,(c)))", "(())", "()", "((()))",
        "(d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,()))))",
    };
    const char *inverted[] = { "(a,(b,c))", "((a,b),((c,d),e))", "(a,(()),b)" };
    const char *trees[] = {
        "(A,(B,(E,K,L),F),(C,G),(D,(H,M),I,J))",
        "(A,(B,(E,H,(I,J,K)),F),(C,G),D)",
    };
    list_pointer L, K, T, U;
    int i;

    /* copy */
    L = read_list("((a,b),((c,d),e))");
    K = copy(L);
    printf("L = ");
    print_linear(L);
    printf("\ncopy(L) = ");
    print_linear(K);
    printf("\nequal(L, copy) = %d, same(L, copy) = %d\n",
           equal(L, K), same(L, K));
    list_clear(L);
    list_clear(K);

    /* equal and same */
    T = read_list("(a,(b,c))");
    U = read_list("(a,(b,d))");
    printf("equal((a,(b,c)), (a,(b,d))) = %d, same = %d\n",
           equal(T, U), same(T, U));
    printf("equal((), ()) = %d, same = %d\n",
           equal(NULL, NULL), same(NULL, NULL));
    list_clear(T);
    list_clear(U);

    /* print_atoms */
    L = read_list("(a,(b),c)");
    printf("print_atoms((a,(b),c)): ");
    print_atoms(L);
    printf("\n");
    list_clear(L);
    L = read_list(trees[0]);
    printf("print_atoms(tree list): ");
    print_atoms(L);
    printf("\n");
    list_clear(L);

    /* depth and iter_depth */
    for (i = 0; i < 7; i++) {
        L = read_list(deep[i]);
        printf("depth %s = %d, iter_depth = %d\n",
               deep[i], depth(L), iter_depth(L));
        list_clear(L);
    }

    /* invert */
    for (i = 0; i < 3; i++) {
        L = read_list(inverted[i]);
        invert(&L);
        printf("invert %s -> ", inverted[i]);
        print_linear(L);
        printf("\n");
        list_clear(L);
    }

    /* print_tree */
    for (i = 0; i < 2; i++) {
        L = read_list(trees[i]);
        printf("print_tree: ");
        print_tree(L);
        printf("\n");
        list_clear(L);
    }
    return 0;
}

/* Expected output:
 * L = ((a,b),((c,d),e))
 * copy(L) = ((a,b),((c,d),e))
 * equal(L, copy) = 1, same(L, copy) = 1
 * equal((a,(b,c)), (a,(b,d))) = 0, same = 0
 * equal((), ()) = 1, same = 1
 * print_atoms((a,(b),c)): abc
 * print_atoms(tree list): ABEKLFCGDHMIJ
 * depth (a,b) = 1, iter_depth = 1
 * depth (a,(b,c)) = 2, iter_depth = 2
 * depth (a,(b,(c))) = 3, iter_depth = 3
 * depth (()) = 1, iter_depth = 1
 * depth () = 0, iter_depth = 0
 * depth ((())) = 2, iter_depth = 2
 * depth (d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,())))) = 5, iter_depth = 5
 * invert (a,(b,c)) -> ((c,b),a)
 * invert ((a,b),((c,d),e)) -> ((e,(d,c)),(b,a))
 * invert (a,(()),b) -> (b,(()),a)
 * print_tree: A(B(E(K,L),F),C(G),D(H(M),I,J))
 * print_tree: A(B(E(H,I(J,K)),F),C(G),D)
 */
