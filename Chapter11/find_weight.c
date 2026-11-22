/* Exam question: the weight of the item that contains x = the depth of the
 * subtree rooted at that item. The solution is the composition of two
 * known routines: depth(tree_search(L, x)). Local prototypes are declared
 * inside the routine; depth uses the max function, not a macro.
 * Examples from the notes: in the tree with root 2 and children 10 and 20,
 * for 2, 10, 20, 30 (2, 1, 1, 0); in the deletion example tree, for 40, 60,
 * 50, 56 (6, 5, 4, 1).
 * Slide: "Exam Question: The Weight of a Node". */
#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};

int FindWeight(tree_ptr L, int x) {
  /* tree_search: node holding x, or NULL */
  tree_ptr tree_search(tree_ptr L, int x);
  int depth(tree_ptr L);
  return depth(tree_search(L, x));
}
tree_ptr tree_search(tree_ptr L, int x) {
  if (!L) return NULL;
  if (L->data == x) return L;
  tree_ptr T = tree_search(L->left, x);
  return T ? T : tree_search(L->right, x);
}
int depth(tree_ptr L) {
  int max(int a, int b);  /* not smaller than a, b */
  return L ? max(depth(L->left),
                 depth(L->right)) + 1 : 0;
}

/* not on the slides: the max function (from the lecture notes) */
int max(int a, int b) { return a > b ? a : b; }

/* not on the slides: the body of get_node (the implementation in the lecture notes) */
tree_ptr get_node(void) {
    tree_ptr r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    r->left = r->right = NULL;
    return r;
}

/* not on the slides: insert from the slide "Why tree_ptr *L", to build the tree */
tree_ptr insert(tree_ptr L, int x) {
  if (!L) {
    L = get_node();
    L->data = x;
  } else if (x < L->data)
    L->left = insert(L->left, x);
  else if (x > L->data)
    L->right = insert(L->right, x);
  return L;        /* root = insert(root, x); */
}

/* not on the slides: gives the tree back to memory (root last) */
static void tree_free(tree_ptr L) {
    if (L) {
        tree_free(L->left);
        tree_free(L->right);
        free(L);
    }
}

int main(void)
{
    /* a tree that is not a search tree: 2(10, 20) */
    tree_ptr K = get_node();
    K->data = 2;
    K->left = get_node();
    K->left->data = 10;
    K->right = get_node();
    K->right->data = 20;
    int x1[] = {2, 10, 20, 30};
    for (int i = 0; i < 4; i++)
        printf("FindWeight(K, %d) = %d\n", x1[i], FindWeight(K, x1[i]));

    int order[] = {40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52, 57, 66, 56};
    tree_ptr L = NULL;
    for (int i = 0; i < 15; i++)
        L = insert(L, order[i]);
    int x2[] = {40, 60, 50, 56};
    for (int i = 0; i < 4; i++)
        printf("FindWeight(L, %d) = %d\n", x2[i], FindWeight(L, x2[i]));
    printf("FindWeight(NULL, 5) = %d\n", FindWeight(NULL, 5));

    tree_free(K);
    tree_free(L);
    return 0;
}

/* Expected output:
 * FindWeight(K, 2) = 2
 * FindWeight(K, 10) = 1
 * FindWeight(K, 20) = 1
 * FindWeight(K, 30) = 0
 * FindWeight(L, 40) = 6
 * FindWeight(L, 60) = 5
 * FindWeight(L, 50) = 4
 * FindWeight(L, 56) = 1
 * FindWeight(NULL, 5) = 0
 */
