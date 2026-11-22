/* Exam question: SWAP between two recursive calls. The routine processes
 * the left subtree, swaps the children, then processes the new right child
 * (that is, the old left one that was just processed) again. The result is
 * not a mirror image: only the two subtrees of the root trade places.
 * Example from the notes: the binary search tree built from 44, 30, 15,
 * 18, 86, 97, 65, 113, 74, 129.
 * Slide: "Exam Question: SWAP Between the Two Recursive Calls". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: the SWAP macro given in the notes */
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};

void proc(tree_ptr L) {
  tree_ptr p;
  if (L) {
    proc(L->left);
    SWAP(L->left, L->right, p);
    proc(L->right);
  }
}

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

/* not on the slides: prints the tree as root(left, right), "-" for an empty subtree */
static void show(tree_ptr L) {
    if (!L) { printf("-"); return; }
    printf("%d", L->data);
    if (L->left || L->right) {
        printf("(");
        show(L->left);
        printf(", ");
        show(L->right);
        printf(")");
    }
}

/* not on the slides: inorder */
static void inorder(tree_ptr L) {
    if (L) {
        inorder(L->left);
        printf(" %d", L->data);
        inorder(L->right);
    }
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
    int order[] = {44, 30, 15, 18, 86, 97, 65, 113, 74, 129};
    tree_ptr L = NULL;
    for (int i = 0; i < 10; i++)
        L = insert(L, order[i]);
    printf("before: ");
    show(L);
    printf("\n");
    proc(L);
    printf("after:  ");
    show(L);
    printf("\ninorder:");
    inorder(L);
    printf("\n");
    tree_free(L);
    return 0;
}

/* Expected output:
 * before: 44(30(15(-, 18), -), 86(65(-, 74), 97(-, 113(-, 129))))
 * after:  44(86(65(-, 74), 97(-, 113(-, 129))), 30(15(-, 18), -))
 * inorder: 65 74 86 97 113 129 44 15 18 30
 */
