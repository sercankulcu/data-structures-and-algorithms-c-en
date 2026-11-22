/* Insertion into a binary search tree: the iterative bst_insert (q trails,
 * p leads, the root comes by address) and the recursive insert that
 * returns the new root. Example from the notes: 47, 55, 49, 26, 34, 17,
 * 52, 84, 93 are inserted with each routine separately; then 50 (inserted)
 * and 47 (already there) are tried.
 * Slides: "How Does Insertion Work?", "bst_insert(50, &L) Step by Step",
 * "Why tree_ptr *L? What Does It Cost?". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;
typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int       data;
    tree_ptr right;
};
/* get_node(): malloc + NULL check,
   sets both children to NULL */

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

boolean bst_insert(int x, tree_ptr *L) {
  tree_ptr q = NULL, p = *L, r; // q trails p
  while (p) {                    // down to NULL
    q = p;                       // q follows p
    if (x < p->data) p = p->left;
    else if (x > p->data) p = p->right;
    else { printf("Duplicate key.\n");
           return FALSE; }
  }
  r = get_node();                // children NULL
  r->data = x;
  if (*L == NULL) *L = r;        // empty: root
  else if (x < q->data) q->left = r;
  else q->right = r;
  return TRUE;
}

/* Recursive version: returns the new root */
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

/* not on the slides: preorder (a space before every value) */
static void preorder(tree_ptr L) {
    if (L) {
        printf(" %d", L->data);
        preorder(L->left);
        preorder(L->right);
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
    int order[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    tree_ptr L = NULL;      /* with bst_insert */
    tree_ptr root = NULL;   /* with insert */
    for (int i = 0; i < 9; i++) {
        bst_insert(order[i], &L);
        root = insert(root, order[i]);
    }
    printf("preorder (iterative):");
    preorder(L);
    printf("\npreorder (recursive):");
    preorder(root);
    printf("\ninorder:");
    inorder(L);
    printf("\n");

    int s = (int) bst_insert(50, &L);
    printf("bst_insert(50) = %d\n", s);
    s = (int) bst_insert(47, &L);
    printf("bst_insert(47) = %d\n", s);
    printf("preorder:");
    preorder(L);
    printf("\n");

    root = insert(root, 47);    /* an equal value is silently rejected */
    printf("preorder after insert(root, 47):");
    preorder(root);
    printf("\n");

    tree_free(L);
    tree_free(root);
    return 0;
}

/* Expected output:
 * preorder (iterative): 47 26 17 34 55 49 52 84 93
 * preorder (recursive): 47 26 17 34 55 49 52 84 93
 * inorder: 17 26 34 47 49 52 55 84 93
 * bst_insert(50) = 1
 * Duplicate key.
 * bst_insert(47) = 0
 * preorder: 47 26 17 34 55 49 52 50 84 93
 * preorder after insert(root, 47): 47 26 17 34 55 49 52 84 93
 */
