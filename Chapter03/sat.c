/* Satisfiability (SAT) by brute force: the formula tree is evaluated in
 * postorder; the 2^3 assignments of 3 variables are generated from the
 * bits of the counter m.
 * Formula (from the notes): (x1 AND NOT x2) OR (NOT x1 AND x3) OR NOT x3.
 * Slides: "SAT: Evaluating the Tree", "SAT Brute Force Step by Step".
 * The helpers that build the tree are not on the slides; the versions from
 * the lecture notes are used. */
#include <stdio.h>
#include <stdlib.h>

typedef enum { L_NOT, L_AND, L_OR, L_TRUE, L_FALSE } logical;
typedef struct node *tree_ptr;
struct node {
  tree_ptr left_child, right_child;
  logical data;
  short value;
};

void post_order_eval(tree_ptr t) {
  if (t) {
    post_order_eval(t->left_child);
    post_order_eval(t->right_child);
    switch (t->data) {
      case L_NOT: t->value = !t->right_child->value; break;
      case L_AND: t->value = t->left_child->value
                         && t->right_child->value; break;
      case L_OR:  t->value = t->left_child->value
                         || t->right_child->value; break;
      case L_TRUE:  t->value = 1; break;
      case L_FALSE: t->value = 0; break;
    }
  }
}

/* not on the slides (from the lecture notes): node creation and tree deletion */
tree_ptr new_node(logical v, tree_ptr left, tree_ptr right) {
  tree_ptr p = malloc(sizeof *p);
  if (p == NULL) {               /* out of memory */
    fprintf(stderr, "out of memory\n");
    exit(EXIT_FAILURE);
  }
  p->data = v;
  p->left_child = left;
  p->right_child = right;
  p->value = 0;
  return p;
}

void free_tree(tree_ptr t) {     /* postorder: children first */
  if (t) {
    free_tree(t->left_child);
    free_tree(t->right_child);
    free(t);
  }
}

/* not on the slides (from the lecture notes): the formula tree and setting the assignment */
tree_ptr leaf[5];   /* leaves: x1, x2, x1, x3, x3 */

tree_ptr build_formula(void) {
  int k;
  for (k = 0; k < 5; k++)
    leaf[k] = new_node(L_FALSE, NULL, NULL);
  /* (x1 AND NOT x2) OR (NOT x1 AND x3) OR NOT x3 */
  return new_node(L_OR,
           new_node(L_OR,
             new_node(L_AND, leaf[0], new_node(L_NOT, NULL, leaf[1])),
             new_node(L_AND, new_node(L_NOT, NULL, leaf[2]), leaf[3])),
           new_node(L_NOT, NULL, leaf[4]));
}

void set_leaves(tree_ptr root, int x1, int x2, int x3) {
  (void)root;           /* the leaves are reached directly through leaf[] */
  leaf[0]->data = x1 ? L_TRUE : L_FALSE;
  leaf[1]->data = x2 ? L_TRUE : L_FALSE;
  leaf[2]->data = x1 ? L_TRUE : L_FALSE;
  leaf[3]->data = x3 ? L_TRUE : L_FALSE;
  leaf[4]->data = x3 ? L_TRUE : L_FALSE;
}

int main(void) {  /* not on the slides: the loop is from the "SAT Brute Force" slide */
  tree_ptr root = build_formula();
  int m, x1, x2, x3;
  for (m = 0; m < 8; m++) {    /* 2^3 assignments */
    x1 = (m >> 2) & 1;
    x2 = (m >> 1) & 1;
    x3 = m & 1;
    set_leaves(root, x1, x2, x3);
    post_order_eval(root);
    if (root->value)
      printf("%d%d%d\n", x1, x2, x3);
  }
  free_tree(root);
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
