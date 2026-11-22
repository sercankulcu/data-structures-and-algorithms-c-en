/* Stackless traversal of a threaded binary tree: finding the inorder
 * successor, inorder traversal that starts at the head node and moves from
 * successor to successor until it returns to the head, and finding the
 * preorder successor. The tree is built with insert_left and insert_right.
 * Main example of the notes (Example 12.1): A(B(D(H, I), E), C(F, G));
 * inorder H D I B E A F C G, preorder A B D H I E C F G.
 * Slides: "Thread Flags", "Finding the Successor", "Threaded Traversal
 * Step by Step", "Threaded Preorder Traversal", "insert_right() Step by
 * Step", "Insert Left Solution". */
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

thread_ptr presucc(thread_ptr p) {
  if (!p->left_thread)       // the left child if there is one
    return p->left_child;
  while (p->right_thread)    // climb the threads
    p = p->right_child;
  return p->right_child;     // the first real right child
}

/* not on the slides: preorder traversal, like tinorder */
static void tpreorder(thread_ptr L) {
    thread_ptr p = L;
    for (;;) {
        p = presucc(p);
        if (p == L) break;
        printf("%c ", p->data);
    }
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
static void reverse_inorder(thread_ptr L) {
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

int main(void)
{
    thread_ptr L = empty_threaded_tree();
    printf("empty tree, inorder: ");
    tinorder(L);                         /* prints nothing */
    printf("\n");

    /* A(B(D(H, I), E), C(F, G)) */
    thread_ptr d[9];
    const char *names = "ABCDEFGHI";
    for (int i = 0; i < 9; i++)
        d[i] = new_node(names[i]);
    thread_ptr A = d[0], B = d[1], C = d[2], D = d[3], E = d[4],
               F = d[5], G = d[6], H = d[7], I = d[8];
    insert_left(L, A);                   /* first node: left of the head */
    insert_left(A, B);  insert_right(A, C);
    insert_left(B, D);  insert_right(B, E);
    insert_left(C, F);  insert_right(C, G);
    insert_left(D, H);  insert_right(D, I);

    printf("succ(head) = %c\n", insucc(L)->data);
    printf("succ(A) = %c, succ(I) = %c\n",
           insucc(A)->data, insucc(I)->data);
    printf("succ(G) is the head: %s\n",
           insucc(G) == L ? "yes" : "no");

    printf("inorder: ");
    tinorder(L);
    printf("\npreorder: ");
    tpreorder(L);
    printf("\nreverse inorder: ");
    reverse_inorder(L);
    printf("\n");

    threaded_tree_free(L);
    return 0;
}

/* Note: the first line and the three traversal lines end with a space. */
/* Expected output:
 * empty tree, inorder:
 * succ(head) = H
 * succ(A) = F, succ(I) = B
 * succ(G) is the head: yes
 * inorder: H D I B E A F C G
 * preorder: A B D H I E C F G
 * reverse inorder: G C F A E B I D H
 */
