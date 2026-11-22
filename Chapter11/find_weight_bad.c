/* Exam question: how many times is the bad FindWeight, which tries to solve
 * the same problem, called? Because it calls each subtree twice, it takes
 * Theta(2^n) on a chain and Theta(n^2) on a balanced tree; moreover, since
 * the results of the calls inside the conditions are not used, it always
 * returns 0 when x is not at the root. The program shows this wrong result
 * too; the code has no undefined behavior.
 * Example from the notes: in the tree with root 2 and children 10 and 20,
 * 14 calls for x = 20 and 21 calls for x = 30; 61 calls on a 4-node chain
 * when x is absent.
 * Slide: "Exam Question: How Many Times Does FindWeight Run?". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: the node type (from the slide "How Insertion Works") */
typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};
typedef tree_ptr item_ptr;    /* not on the slides: the type name used in the question */

static long calls = 0;        /* not on the slides: call counter */

/* not on the slides: weight(L) = the depth of the subtree rooted at L */
static int weight(item_ptr L) {
    if (!L) return 0;
    int l = weight(L->left), r = weight(L->right);
    return (l > r ? l : r) + 1;
}

int FindWeight(item_ptr L, int x) {
  calls++;                    /* not on the slides: counter */
  if (!L) return 0;
  else if (L->data == x) return weight(L);
  if (FindWeight(L->left, x) >
      FindWeight(L->right, x))
    FindWeight(L->left, x);
  if (FindWeight(L->right, x) >
      FindWeight(L->left, x))
    FindWeight(L->right, x);
  return 0;
}

/* not on the slides: allocates a single node */
static tree_ptr make_node(int x) {
    tree_ptr r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    r->data = x;
    r->left = r->right = NULL;
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

/* not on the slides: prints the result and the number of calls */
static void measure(const char *name, item_ptr L, int x) {
    calls = 0;
    int a = FindWeight(L, x);
    printf("%s, x = %d: returned = %d, calls = %ld\n", name, x, a, calls);
}

int main(void)
{
    /* 2(10, 20) */
    tree_ptr K = make_node(2);
    K->left = make_node(10);
    K->right = make_node(20);
    measure("2(10, 20)", K, 2);
    measure("2(10, 20)", K, 20);   /* the correct answer is 1 */
    measure("2(10, 20)", K, 30);

    /* right chain 1 -> 2 -> 3 -> 4 */
    tree_ptr Z = make_node(1), p = Z;
    for (int i = 2; i <= 4; i++) {
        p->right = make_node(i);
        p = p->right;
    }
    measure("4-node chain", Z, 99);

    tree_free(K);
    tree_free(Z);
    return 0;
}

/* Expected output:
 * 2(10, 20), x = 2: returned = 2, calls = 1
 * 2(10, 20), x = 20: returned = 0, calls = 14
 * 2(10, 20), x = 30: returned = 0, calls = 21
 * 4-node chain, x = 99: returned = 0, calls = 61
 */
