/* One-line depth and the macro trap: since MAX is a macro, the call for the
 * larger subtree is executed twice. The result is correct but the number
 * of calls grows to 3 * 2^n - 2 on a chain (the version with local
 * variables makes 2n + 1 calls). Measurements from the notes: chains of 4
 * and 12 nodes; also a full tree of 7 nodes.
 * Slide: "On Adding Extra Parameters" (the one-line depth and the MAX macro). */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* not on the slides: the macro given in the notes */

typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};

static long calls = 0;   /* not on the slides: call counter */

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

int depth(tree_ptr L) {    /* one line */
  calls++;                 /* not on the slides: counter */
  return !L ? 0 : MAX(depth(L->left),
                      depth(L->right)) + 1;
}

/* not on the slides: gives the tree back to memory (root last) */
static void tree_free(tree_ptr L) {
    if (L) {
        tree_free(L->left);
        tree_free(L->right);
        free(L);
    }
}

/* not on the slides: prints the depth and the number of calls */
static void measure(const char *name, int n, tree_ptr L) {
    calls = 0;
    int d = depth(L);
    printf("%s (n = %d): depth = %d, calls = %ld, 2n + 1 = %d\n",
           name, n, d, calls, 2 * n + 1);
}

int main(void)
{
    tree_ptr z4 = NULL, z12 = NULL, full = NULL;
    for (int i = 1; i <= 4; i++) z4 = insert(z4, i);      /* right chain */
    for (int i = 1; i <= 12; i++) z12 = insert(z12, i);
    int order[] = {4, 2, 6, 1, 3, 5, 7};                  /* 3 full levels */
    for (int i = 0; i < 7; i++) full = insert(full, order[i]);

    measure("chain", 4, z4);
    measure("chain", 12, z12);
    measure("full tree", 7, full);

    tree_free(z4);
    tree_free(z12);
    tree_free(full);
    return 0;
}

/* Expected output:
 * chain (n = 4): depth = 4, calls = 46, 2n + 1 = 9
 * chain (n = 12): depth = 12, calls = 12286, 2n + 1 = 25
 * full tree (n = 7): depth = 3, calls = 40, 2n + 1 = 15
 */
