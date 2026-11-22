/* Deletion from a binary search tree: link (a pointer to pointer) holds
 * the link that leads to p; for a node with two children, the largest node
 * of the left subtree is moved up. Example from the notes: 60 is deleted
 * from the tree built from 40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52,
 * 57, 66, 56 (57 moves up, 56 moves to the right of 55, the depth drops
 * from 6 to 5). Then 99, which is not in the tree, is requested, and at
 * the end all values are deleted to empty the tree.
 * Slide: "bst_delete(60, &L): A Node with Two Children". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* not on the slides: the macro given in the notes */

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

/* not on the slides: depth from the slide "depth() Step by Step" */
int depth(tree_ptr L) {
  int left, right;
  if (L) {                   // pointer NULL?
    left = depth(L->left);
    right = depth(L->right);
    return MAX(left, right) + 1;
  }
  else return 0;             // reached past a leaf
}

void bst_delete(int x, tree_ptr *L) {
  tree_ptr p = *L, *link = L;  // link to p
  while (p && p->data != x) {  // find x
    link = (x < p->data) ? &p->left
                        : &p->right;
    p = *link;
  }
  if (!p) return;              // x absent
  if (p->left && p->right) {  // 2 children
    tree_ptr *b = &p->left;     // left subtree's
    while ((*b)->right)           // largest
      b = &(*b)->right;           // node
    p->data = (*b)->data;      // move the data
    link = b;  p = *b;          // delete it
  }
  *link = p->left ? p->left : p->right;
  free(p);
}

/* not on the slides: inorder */
static void inorder(tree_ptr L) {
    if (L) {
        inorder(L->left);
        printf(" %d", L->data);
        inorder(L->right);
    }
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

/* not on the slides: prints the state of the tree */
static void state(tree_ptr L) {
    printf("tree: ");
    show(L);
    printf("\ninorder:");
    inorder(L);
    printf("\ndepth: %d\n", depth(L));
}

int main(void)
{
    int order[] = {40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52, 57, 66, 56};
    tree_ptr L = NULL;
    for (int i = 0; i < 15; i++)
        L = insert(L, order[i]);
    state(L);

    printf("-- bst_delete(60)\n");
    bst_delete(60, &L);
    state(L);

    printf("-- bst_delete(99)\n");
    bst_delete(99, &L);    /* absent: the tree does not change */
    printf("depth: %d\n", depth(L));

    for (int i = 0; i < 15; i++)
        bst_delete(order[i], &L);  /* 60 is gone by now; that call does nothing */
    printf("all deleted, L is %s\n", L == NULL ? "NULL" : "not NULL");
    return 0;
}

/* Expected output:
 * tree: 40(20(10, 30), 60(50(42, 55(52, 57(56, -))), 70(65(-, 66), 73)))
 * inorder: 10 20 30 40 42 50 52 55 56 57 60 65 66 70 73
 * depth: 6
 * -- bst_delete(60)
 * tree: 40(20(10, 30), 57(50(42, 55(52, 56)), 70(65(-, 66), 73)))
 * inorder: 10 20 30 40 42 50 52 55 56 57 65 66 70 73
 * depth: 5
 * -- bst_delete(99)
 * depth: 5
 * all deleted, L is NULL
 */
