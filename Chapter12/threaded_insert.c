/* Inserting nodes into a threaded tree. Case 1: the parent has no right
 * subtree, the six assignments from the slides are enough. Case 2: the
 * parent has a right subtree; insert_right takes the child's right thread
 * from the parent and redirects the successor's left thread to the child.
 * insert_left is its mirror image. Reverse traversal shows that the left
 * threads are correct too.
 * Examples from the notes: in A(-, B(C, -)), D goes to the right of B
 * (Case 1); in A(-, B(C, D(E, F))), insert_right(B, X) (Case 2);
 * in A(B(D, E), C), insert_left(A, X) (Example 12.3).
 * Slides: "Insertion Intro", "Case 1 Step by Step",
 * "insert_right() Step by Step", "Insert Left Solution". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;   /* not on the slides: TRUE/FALSE */

typedef struct threaded_tree *thread_ptr;
struct threaded_tree {
    short int  left_thread;  /* TRUE: left_child is a thread */
    thread_ptr left_child;
    char       data;
    thread_ptr right_child;
    short int  right_thread; /* TRUE: right_child is a thread */
};

/* not on the slides: node allocation and empty tree (helpers from the notes) */
thread_ptr new_node(char data) {
    thread_ptr d = malloc(sizeof *d);
    if (d == NULL) {           // out of memory
        fprintf(stderr, "out of memory\n");
        exit(EXIT_FAILURE);
    }
    d->data = data;
    d->left_child = d->right_child = NULL;   // the insert routine fills them in
    d->left_thread = d->right_thread = TRUE;
    return d;
}
thread_ptr empty_threaded_tree(void) {
    thread_ptr L = new_node('-');  // head node: its data is unused
    L->left_child = L;  L->left_thread = TRUE;    // the tree is empty
    L->right_child = L; L->right_thread = FALSE;  // right always points to itself
    return L;
}

/* not on the slides: routines from the "Finding the Successor" and
   "Threaded Traversal" slides */
thread_ptr insucc(thread_ptr L) {
  // successor of the (non-NULL) node L
  thread_ptr p = L->right_child;
  if (!L->right_thread)      // is there a right subtree?
    while (!p->left_thread)  // go down to its leftmost node
      p = p->left_child;
  return p;
}

void tinorder(thread_ptr L) {
  thread_ptr p = L;          // L: the head node
  for (;;) {
    p = insucc(p);
    if (p == L) break;       // back at the head?
    printf("%c ", p->data);
  }
}

/* not on the slides: the six assignments of the "Insertion Intro" /
   "Case 1 Step by Step" slides wrapped in a function header; correct
   only when parent has no right subtree */
static void case1_insert(thread_ptr parent, thread_ptr child) {
child->right_child  = parent->right_child;
child->right_thread = TRUE;  // parent had no right subtree
child->left_child  = parent;
child->left_thread = TRUE;
parent->right_child  = child;
parent->right_thread = FALSE;  // was TRUE
}

void insert_right(thread_ptr parent,
                  thread_ptr child) {
  // make child the right child of parent (threaded)
  thread_ptr p;
  child->right_child  = parent->right_child;
  child->right_thread = parent->right_thread;
  child->left_child   = parent;
  child->left_thread  = TRUE;
  parent->right_child  = child;
  parent->right_thread = FALSE;
  if (!child->right_thread) { // did the parent have a subtree?
    p = insucc(child);
    p->left_child = child;     // the successor's predecessor is child
  }
}

thread_ptr inpred(thread_ptr L) {
  thread_ptr p = L->left_child;
  if (!L->left_thread)
    while (!p->right_thread) p = p->right_child;
  return p;
}
void insert_left(thread_ptr parent, thread_ptr child) {
  child->left_child   = parent->left_child;
  child->left_thread  = parent->left_thread;
  child->right_child  = parent;
  child->right_thread = TRUE;    // successor: the parent
  parent->left_child  = child;
  parent->left_thread = FALSE;
  if (!child->left_thread) {     // the parent had a left subtree
    thread_ptr p = inpred(child);
    p->right_child = child;      // the predecessor's successor is child
  }
}

/* not on the slides: reverse inorder traversal (predecessor to predecessor) */
static void reverse_tinorder(thread_ptr L) {
    thread_ptr p = L;
    for (;;) {
        p = inpred(p);
        if (p == L) break;
        printf("%c ", p->data);
    }
}

/* not on the slides: frees the tree (routine from the notes) */
void threaded_tree_free(thread_ptr L) {
    thread_ptr p = insucc(L), next;
    while (p != L) {
        next = insucc(p);   // find the successor first
        free(p);            // then release the node
        p = next;
    }
    free(L);                // the head last
}

/* not on the slides: traverses in both directions and prints */
static void show(const char *title, thread_ptr L) {
    printf("%s\n  inorder:  ", title);
    tinorder(L);
    printf("\n  reverse:  ");
    reverse_tinorder(L);
    printf("\n");
}

/* not on the slides: the name of the node a thread points to */
static char name(thread_ptr p, thread_ptr head) {
    return p == head ? '^' : p->data;   /* ^ = head */
}

int main(void)
{
    /* Case 1: A(-, B(C, -)), D goes to the right of B */
    thread_ptr L = empty_threaded_tree();
    thread_ptr A = new_node('A'), B = new_node('B'),
               C = new_node('C'), D = new_node('D');
    insert_left(L, A);
    insert_right(A, B);
    insert_left(B, C);
    case1_insert(B, D);
    show("Case 1: D to the right of B (six assignments)", L);
    printf("  D: left thread -> %c, right thread -> %c\n",
           name(D->left_child, L), name(D->right_child, L));
    threaded_tree_free(L);

    /* Case 2: A(-, B(C, D(E, F))), insert_right(B, X) */
    L = empty_threaded_tree();
    A = new_node('A');  B = new_node('B');
    C = new_node('C');  D = new_node('D');
    thread_ptr E = new_node('E'), F = new_node('F'),
               X = new_node('X');
    insert_left(L, A);
    insert_right(A, B);
    insert_left(B, C);
    insert_right(B, D);
    insert_left(D, E);
    insert_right(D, F);
    printf("Before Case 2, E: left thread -> %c\n", name(E->left_child, L));
    insert_right(B, X);
    show("Case 2: insert_right(B, X)", L);
    printf("  X: left thread -> %c, right child -> %c; E: left thread -> %c\n",
           name(X->left_child, L), name(X->right_child, L),
           name(E->left_child, L));
    threaded_tree_free(L);

    /* Example 12.3: A(B(D, E), C), insert_left(A, X) */
    L = empty_threaded_tree();
    A = new_node('A');  B = new_node('B');
    C = new_node('C');  D = new_node('D');
    E = new_node('E');  X = new_node('X');
    insert_left(L, A);
    insert_left(A, B);
    insert_right(A, C);
    insert_left(B, D);
    insert_right(B, E);
    insert_left(A, X);
    show("Example 12.3: insert_left(A, X)", L);
    printf("  E: right thread -> %c\n", name(E->right_child, L));
    threaded_tree_free(L);
    return 0;
}

/* Note: the traversal lines end with a space; ^ is the head. */
/* Expected output:
 * Case 1: D to the right of B (six assignments)
 *   inorder:  A C B D
 *   reverse:  D B C A
 *   D: left thread -> B, right thread -> ^
 * Before Case 2, E: left thread -> B
 * Case 2: insert_right(B, X)
 *   inorder:  A C B X E D F
 *   reverse:  F D E X B C A
 *   X: left thread -> B, right child -> D; E: left thread -> X
 * Example 12.3: insert_left(A, X)
 *   inorder:  D B E X A C
 *   reverse:  C A X E B D
 *   E: right thread -> X
 */
