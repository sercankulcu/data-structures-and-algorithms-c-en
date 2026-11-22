/* Satisfiability (SAT) by brute force: the formula tree is evaluated in
 * postorder; the 2^3 assignments of 3 variables are generated from the
 * bits of the counter m.
 * Formula (from the notes): (x1 AND NOT x2) OR (NOT x1 AND x3) OR NOT x3.
 * Slides: "SAT: Evaluating the Tree", "SAT Brute Force Step by Step".
 * The helpers that build the tree are not on the slides; the versions from
 * the lecture notes are used. */
#include <stdio.h>
#include <stdlib.h>

typedef enum { NOT_N, AND_N, OR_N, TRUE_N, FALSE_N } logic;
typedef struct tree_node *tree_ptr;
struct tree_node {
  tree_ptr left, right;
  logic data;
  short value;
};

void post_eval(tree_ptr L) {
  if (L) {
    post_eval(L->left);
    post_eval(L->right);
    switch (L->data) {
      case NOT_N: L->value = !L->right->value; break;
      case AND_N: L->value = L->left->value
                         && L->right->value; break;
      case OR_N:  L->value = L->left->value
                         || L->right->value; break;
      case TRUE_N:  L->value = 1; break;
      case FALSE_N: L->value = 0; break;
    }
  }
}

/* not on the slides (from the lecture notes): node creation and tree deletion */
tree_ptr new_node(logic v, tree_ptr l, tree_ptr r) {
  tree_ptr p = malloc(sizeof *p);
  if (p == NULL) {               /* out of memory */
    fprintf(stderr, "out of memory\n");
    exit(EXIT_FAILURE);
  }
  p->data = v;
  p->left = l;
  p->right = r;
  p->value = 0;
  return p;
}

void tree_free(tree_ptr L) {     /* postorder: children first */
  if (L) {
    tree_free(L->left);
    tree_free(L->right);
    free(L);
  }
}

/* not on the slides (from the lecture notes): the formula tree and setting the assignment */
tree_ptr leaf[5];   /* leaves: x1, x2, x1, x3, x3 */

tree_ptr build_formula(void) {
  int k;
  for (k = 0; k < 5; k++)
    leaf[k] = new_node(FALSE_N, NULL, NULL);
  /* (x1 AND NOT x2) OR (NOT x1 AND x3) OR NOT x3 */
  return new_node(OR_N,
           new_node(OR_N,
             new_node(AND_N, leaf[0], new_node(NOT_N, NULL, leaf[1])),
             new_node(AND_N, new_node(NOT_N, NULL, leaf[2]), leaf[3])),
           new_node(NOT_N, NULL, leaf[4]));
}

void set_leaves(tree_ptr root, int x1, int x2, int x3) {
  (void)root;           /* the leaves are reached directly through leaf[] */
  leaf[0]->data = x1 ? TRUE_N : FALSE_N;
  leaf[1]->data = x2 ? TRUE_N : FALSE_N;
  leaf[2]->data = x1 ? TRUE_N : FALSE_N;
  leaf[3]->data = x3 ? TRUE_N : FALSE_N;
  leaf[4]->data = x3 ? TRUE_N : FALSE_N;
}

int main(void) {  /* not on the slides: the loop is from the "SAT Brute Force" slide */
  tree_ptr root = build_formula();
  int m, x1, x2, x3;
  for (m = 0; m < 8; m++) {    /* 2^3 assignments */
    x1 = (m >> 2) & 1;
    x2 = (m >> 1) & 1;
    x3 = m & 1;
    set_leaves(root, x1, x2, x3);
    post_eval(root);
    if (root->value)
      printf("%d%d%d\n", x1, x2, x3);
  }
  tree_free(root);
  return 0;
}

/* Only the assignment 111 does not satisfy the formula. */
/* Expected output:
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 */
