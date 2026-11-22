/* Tree routines: copy (the same tree built from new nodes), equal and
 * equal2 (same shape and same data), swap_children (mirror image using the
 * SWAP macro). Examples: a copy of the A...L tree, comparing A(B,C) with
 * A(B,D), swapping the children of A(B(D),C) twice.
 * Slides: "QUESTION: Make a copy of a Tree", "copy(): The Original Tree and Its copy",
 * "QUESTION: Are Two Trees Equivalent (Isomorphic)?", "equal(): A(B,C) vs. A(B,D)",
 * "QUESTION: Write equal() a Different Way", "QUESTION: Swap the Left and Right Children". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

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

/* from the slide "Recursive Traversal Routines", for the output */
void preorder(tree_pointer L) {
  if (L) {
    printf("%c", L->data);
    preorder(L->left_child);
    preorder(L->right_child);
  }
}

void inorder(tree_pointer L) {
  if (L) {
    inorder(L->left_child);
    printf("%c", L->data);
    inorder(L->right_child);
  }
}

tree_pointer copy(tree_pointer L) {
  if (!L) return NULL;
  tree_pointer T = malloc(sizeof *T);
  if (!T) { perror("malloc"); exit(1); }
  T->left_child = copy(L->left_child);
  T->right_child = copy(L->right_child);
  T->data = L->data;
  return T;
}

int equal(tree_pointer L, tree_pointer T) {
  return (!L && !T) ||
         (L && T && L->data == T->data
          && equal(L->left_child, T->left_child)
          && equal(L->right_child, T->right_child));
}

int equal2(tree_pointer L, tree_pointer T) {
  if (L == NULL || T == NULL)
    return L == T;          /* both NULL? */
  if (L->data != T->data)
    return 0;
  if (!equal2(L->left_child, T->left_child))
    return 0;
  return equal2(L->right_child, T->right_child);
}

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void swap_children(tree_pointer L) {
  tree_pointer p;
  if (L) {
    SWAP(L->left_child, L->right_child, p);
    swap_children(L->left_child);
    swap_children(L->right_child);
  }
}

/* not on the slides: helper that builds a tree */
static tree_pointer new_node(char data, tree_pointer left, tree_pointer right)
{
    tree_pointer p = get_node();
    p->data = data;
    p->left_child = left;
    p->right_child = right;
    return p;
}

int main(void)
{
    tree_pointer t, k, L, T, m, m2;

    /* the A...L tree and its copy */
    t = new_node('A',
               new_node('B', NULL,
                     new_node('C',
                           new_node('D', new_node('G', NULL, NULL),
                                         new_node('H', NULL, NULL)),
                           new_node('E', NULL,
                                 new_node('I', new_node('J', NULL, NULL),
                                               new_node('K', NULL, NULL))))),
               new_node('F', new_node('L', NULL, NULL), NULL));
    k = copy(t);
    printf("copy preorder : ");
    preorder(k);
    printf("\ncopy inorder  : ");
    inorder(k);
    printf("\nequal(t, copy) = %d, equal2 = %d, same root: %d\n",
           equal(t, k), equal2(t, k), t == k);

    /* A(B, C) and A(B, D) */
    L = new_node('A', new_node('B', NULL, NULL), new_node('C', NULL, NULL));
    T = new_node('A', new_node('B', NULL, NULL), new_node('D', NULL, NULL));
    printf("equal(A(B,C), A(B,D)) = %d, equal2 = %d\n",
           equal(L, T), equal2(L, T));

    /* A(B(D), C): swap_children */
    m = new_node('A', new_node('B', new_node('D', NULL, NULL), NULL),
                      new_node('C', NULL, NULL));
    m2 = copy(m);
    printf("inorder: ");
    inorder(m);
    swap_children(m);
    printf("\nafter swap_children: ");
    inorder(m);
    printf(", equal(m, original) = %d\n", equal(m, m2));
    swap_children(m);
    printf("second time: ");
    inorder(m);
    printf(", equal(m, original) = %d\n", equal(m, m2));

    tree_free(t);
    tree_free(k);
    tree_free(L);
    tree_free(T);
    tree_free(m);
    tree_free(m2);
    return 0;
}

/* Expected output:
 * copy preorder : ABCDGHEIJKFL
 * copy inorder  : BGDHCEJIKALF
 * equal(t, copy) = 1, equal2 = 1, same root: 0
 * equal(A(B,C), A(B,D)) = 0, equal2 = 0
 * inorder: DBAC
 * after swap_children: CABD, equal(m, original) = 0
 * second time: DBAC, equal(m, original) = 1
 */
