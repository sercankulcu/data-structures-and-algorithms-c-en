/* Traversal with a stack (without recursion): inorder, preorder (two
 * solutions), postorder, and printing only the leaves during an inorder
 * walk. Node addresses are pushed on the stack; pop returns NULL on an
 * empty stack.
 * Example trees: A(B(D,E),C) and the A...L tree.
 * Slides: "Non-Recursive inorder Traversal", "Inorder with a Stack: A(B(D,E),C)",
 * "Q1: Iterative preorder", "Q2: Iterative postorder", "Q3-6: Printing the Leaves"
 * (second block: the condition in the stack version). */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

#define MAX_SIZE 100  /* not on the slides */

typedef struct node *tree_pointer;
struct node {
    tree_pointer left_child;  /* left subtree */
    char         data;
    tree_pointer right_child; /* right subtree */
};

tree_pointer get_node(void) {     /* new node */
    tree_pointer p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    p->left_child = p->right_child = NULL;
    return p;
}

void tree_free(tree_pointer L) {  /* postorder */
    if (!L) return;
    tree_free(L->left_child);
    tree_free(L->right_child);
    free(L);
}

void push(int *top, tree_pointer p,
          tree_pointer s[]) {
  if (*top == MAX_SIZE - 1) {
    fprintf(stderr, "Stack is full\n");
    exit(EXIT_FAILURE);
  }
  s[++*top] = p;
}
tree_pointer pop(int *top,
                 tree_pointer s[]) {
  return (*top == -1) ? NULL : s[(*top)--];
}

void iter_inorder(tree_pointer L) {
  tree_pointer stack[MAX_SIZE];
  int top = -1;
  for (;;) {
    for (; L; L = L->left_child) // push lefts
      push(&top, L, stack);
    L = pop(&top, stack);       // NULL if empty
    if (!L) break;
    printf("%c", L->data);
    L = L->right_child;
  }
}

void iter_preorder(tree_pointer L) {
  tree_pointer stack[MAX_SIZE];
  int top = -1;
  for (;;) {
    for (; L; L = L->left_child) {
      printf("%c", L->data);   // print on entry
      push(&top, L, stack);
    }
    L = pop(&top, stack);
    if (!L) break;
    L = L->right_child;
  }
}

/* The second solution of QUESTION 1: the piece on the slide is the body of
 * this function (not in the slides: the function name and the stack
 * declaration). */
void iter_preorder2(tree_pointer L) {
  tree_pointer stack[MAX_SIZE];
  int top = -1;
if (L) push(&top, L, stack);
while ((L = pop(&top, stack))) {
  printf("%c", L->data);
  if (L->right_child)
    push(&top, L->right_child, stack);
  if (L->left_child)
    push(&top, L->left_child, stack);
}
}

void iter_postorder(tree_pointer L) {
  tree_pointer stack[MAX_SIZE], last = NULL, t;
  int top = -1;
  while (L || top != -1) {
    if (L) {                     // go left
      push(&top, L, stack);
      L = L->left_child;
    } else {
      t = stack[top];            // peek at the top
      if (t->right_child && t->right_child != last)
        L = t->right_child;      // right first
      else {
        printf("%c", t->data);
        last = pop(&top, stack);
      }
    }
  }
}

/* QUESTION 5: in the stack version of inorder, the printf line is tied to
 * the condition on the slide (not in the slides: the function name). */
void iter_print_leaves(tree_pointer L) {
  tree_pointer stack[MAX_SIZE];
  int top = -1;
  for (;;) {
    for (; L; L = L->left_child)
      push(&top, L, stack);
    L = pop(&top, stack);
    if (!L) break;
    if (!L->left_child && !L->right_child)
      printf("%c", L->data);
    L = L->right_child;
  }
}

/* not on the slides: helper that builds a tree, and the trial */
static tree_pointer new_node(char data, tree_pointer left, tree_pointer right)
{
    tree_pointer p = get_node();
    p->data = data;
    p->left_child = left;
    p->right_child = right;
    return p;
}

static void try_all(const char *name, tree_pointer t)
{
    printf("%s\n  inorder    : ", name);
    iter_inorder(t);
    printf("\n  preorder   : ");
    iter_preorder(t);
    printf("\n  preorder 2 : ");
    iter_preorder2(t);
    printf("\n  postorder  : ");
    iter_postorder(t);
    printf("\n  leaf nodes : ");
    iter_print_leaves(t);
    printf("\n");
}

int main(void)
{
    tree_pointer t1, t2;

    /* A(B(D, E), C) */
    t1 = new_node('A', new_node('B', new_node('D', NULL, NULL), new_node('E', NULL, NULL)),
                       new_node('C', NULL, NULL));
    /* the A...L tree */
    t2 = new_node('A',
               new_node('B', NULL,
                     new_node('C',
                           new_node('D', new_node('G', NULL, NULL),
                                         new_node('H', NULL, NULL)),
                           new_node('E', NULL,
                                 new_node('I', new_node('J', NULL, NULL),
                                               new_node('K', NULL, NULL))))),
               new_node('F', new_node('L', NULL, NULL), NULL));

    try_all("A(B(D,E),C)", t1);
    try_all("A...L", t2);
    tree_free(t1);
    tree_free(t2);
    return 0;
}

/* Expected output:
 * A(B(D,E),C)
 *   inorder    : DBEAC
 *   preorder   : ABDEC
 *   preorder 2 : ABDEC
 *   postorder  : DEBCA
 *   leaf nodes : DEC
 * A...L
 *   inorder    : BGDHCEJIKALF
 *   preorder   : ABCDGHEIJKFL
 *   preorder 2 : ABCDGHEIJKFL
 *   postorder  : GHDJKIECBLFA
 *   leaf nodes : GHJKL
 */
