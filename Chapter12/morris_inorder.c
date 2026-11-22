/* Morris traversal: stackless inorder traversal of an ordinary binary tree
 * without threads. Before going left, a temporary thread is set up at the
 * predecessor and removed on the second visit; when the traversal ends the
 * tree is back in its original state.
 * Example from the notes (Table 12.9): A(B(D, E), C), output DBEAC.
 * Slide: "Morris Traversal". */
#include <stdio.h>
#include <stdlib.h>

/* not on the slides: the node type from Chapter 11 */
typedef struct node *tree_ptr;
struct node {
    tree_ptr left;
    int      data;
    tree_ptr right;
};

void morris_inorder(tree_ptr L) {
  while (L) {
    if (!L->left) {                 /* no left: print, go right */
      printf("%c", L->data);  L = L->right;
    } else {
      tree_ptr p = L->left;         /* inorder predecessor */
      while (p->right && p->right != L)
        p = p->right;
      if (!p->right) {              /* add a temporary thread */
        p->right = L;  L = L->left;
      } else {                      /* remove the thread */
        p->right = NULL;
        printf("%c", L->data);  L = L->right;
      }
    }
  }
}

/* not on the slides: recursive inorder for comparison (from the notes) */
void inorder(tree_ptr p) {
  if (p) {
    inorder(p->left);
    printf("%c", p->data);
    inorder(p->right);
  }
}

/* not on the slides: allocates one node */
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

/* not on the slides: returns the tree to memory (root last) */
static void free_tree(tree_ptr L) {
    if (L) {
        free_tree(L->left);
        free_tree(L->right);
        free(L);
    }
}

int main(void)
{
    /* A(B(D, E), C) */
    tree_ptr A = make_node('A');
    A->left = make_node('B');
    A->right = make_node('C');
    A->left->left = make_node('D');
    A->left->right = make_node('E');
    tree_ptr D = A->left->left, E = A->left->right;

    printf("morris:    ");
    morris_inorder(A);
    printf("\nrecursive: ");
    inorder(A);
    printf("\nright of D and E is NULL again: %s\n",
           (D->right == NULL && E->right == NULL) ? "yes" : "no");

    free_tree(A);
    return 0;
}

/* Expected output:
 * morris:    DBEAC
 * recursive: DBEAC
 * right of D and E is NULL again: yes
 */
