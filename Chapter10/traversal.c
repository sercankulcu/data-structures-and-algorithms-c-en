/* Linked representation of a binary tree and recursive traversals:
 * preorder, inorder, postorder. Nodes are allocated with get_node and
 * released with tree_free. At the end, the preorder version that does not
 * make NULL calls (it checks before calling) gives the same output.
 * Example trees: A(B(D), C) and the twelve-node A...L tree
 * (A: left B, right F; B: right C; C: D, E; D: G, H; E: right I;
 * I: J, K; F: left L).
 * Slides: "Linked (Pointer) Representation of a Binary Tree", "A New Node: get_node()",
 * "Traversal Routines, Recursively", "Inorder / Preorder / Postorder Traversal Step by Step",
 * "The Cost of Traversal, and NULL Calls". */
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

void postorder(tree_pointer L) {
  if (L) {
    postorder(L->left_child);
    postorder(L->right_child);
    printf("%c", L->data);
  }
}

/* "Cost of Traversal": preorder with the two call lines written in the
 * "after" form (not in the slides: the function name and frame).
 *   before: preorder(L->left_child); preorder(L->right_child);
 *           (n+1 calls on NULL) */
void preorder_checked(tree_pointer L) {
  if (L) {
    printf("%c", L->data);
    /* after: check before calling */
    if (L->left_child) preorder_checked(L->left_child);
    if (L->right_child) preorder_checked(L->right_child);
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

static void three_traversals(const char *name, tree_pointer t)
{
    printf("%s\n  preorder : ", name);
    preorder(t);
    printf("\n  inorder  : ");
    inorder(t);
    printf("\n  postorder: ");
    postorder(t);
    printf("\n");
}

int main(void)
{
    tree_pointer t1, t2;

    /* A(B(D), C) */
    t1 = new_node('A', new_node('B', new_node('D', NULL, NULL), NULL),
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

    three_traversals("A(B(D),C)", t1);
    three_traversals("A...L", t2);
    printf("preorder_checked (A...L): ");
    preorder_checked(t2);
    printf("\n");

    tree_free(t1);
    tree_free(t2);
    return 0;
}

/* Expected output:
 * A(B(D),C)
 *   preorder : ABDC
 *   inorder  : DBAC
 *   postorder: DBCA
 * A...L
 *   preorder : ABCDGHEIJKFL
 *   inorder  : BGDHCEJIKALF
 *   postorder: GHDJKIECBLFA
 * preorder_checked (A...L): ABCDGHEIJKFL
 */
