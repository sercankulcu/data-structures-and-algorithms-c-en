/* Tree depth: a recursive depth with local left/right variables, and an
 * iterative depth_iter that walks level by level without a global variable.
 * Examples from the notes: the tree A(B(D, -), C(E(F, -), -)) (depth 4),
 * the same nine values in two insertion orders (depth 4 and 6) and the
 * empty tree.
 * Slides: "Recursive depth: {Left, Right} Frames", "QUESTION: Write depth Iteratively". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* not on the slides: the macro given in the notes */
#define MAX_SIZE 100                       /* not on the slides: queue size */

typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};

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

int depth(tree_ptr L) {
  int left, right;
  if (L) {                   // pointer NULL?
    left = depth(L->left);
    right = depth(L->right);
    return MAX(left, right) + 1;
  }
  else return 0;             // reached past a leaf
}

/* iterative, no globals:
   walk level by level, count levels */
int depth_iter(tree_ptr L) {
  tree_ptr k[MAX_SIZE];
  int front = 0, rear = 0, d = 0;
  if (L) k[rear++] = L;
  while (front < rear) {          /* one level */
    int last = rear;
    d++;
    for (; front < last; front++) {
      if (k[front]->left) k[rear++] = k[front]->left;
      if (k[front]->right) k[rear++] = k[front]->right;
    }
  }
  return d;       /* needs MAX_SIZE >= n */
}

/* not on the slides: a single node with a letter */
static tree_ptr make_node(int x) {
    tree_ptr r = get_node();
    r->data = x;
    return r;
}

/* not on the slides: gives the tree back to memory (root last) */
static void tree_free(tree_ptr L) {
    if (L) {
        tree_free(L->left);
        tree_free(L->right);
        free(L);
    }
}

/* not on the slides: prints the results of the two routines */
static void show(const char *name, tree_ptr L) {
    printf("%s: depth = %d, depth_iter = %d\n",
           name, depth(L), depth_iter(L));
}

int main(void)
{
    /* A(B(D, -), C(E(F, -), -)) */
    tree_ptr A = make_node('A');
    A->left = make_node('B');
    A->right = make_node('C');
    A->left->left = make_node('D');
    A->right->left = make_node('E');
    A->right->left->left = make_node('F');
    show("A..F tree", A);

    int order1[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    int order2[] = {26, 17, 47, 93, 84, 52, 34, 55, 49};
    tree_ptr T1 = NULL, T2 = NULL;
    for (int i = 0; i < 9; i++) {
        T1 = insert(T1, order1[i]);
        T2 = insert(T2, order2[i]);
    }
    show("order starting with 47", T1);
    show("order starting with 26", T2);
    show("empty tree", NULL);

    tree_free(A);
    tree_free(T1);
    tree_free(T2);
    return 0;
}

/* Expected output:
 * A..F tree: depth = 4, depth_iter = 4
 * order starting with 47: depth = 4, depth_iter = 4
 * order starting with 26: depth = 6, depth_iter = 6
 * empty tree: depth = 0, depth_iter = 0
 */
