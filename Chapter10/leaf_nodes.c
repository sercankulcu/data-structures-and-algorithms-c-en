/* Conditional traversal: printing the leaves from left to right and
 * printing only the nodes that have just a left child. Example A...L tree:
 * the leaves are GHJKL, the only node with just a left child is F.
 * Slides: "Q3-6: Printing the Leaves" (first block), "Q7-9: Selecting Nodes by Number of Children". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

typedef struct tree *tree_pointer;
struct tree {
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

void print_leaves(tree_pointer L) {
  if (L) {
    print_leaves(L->left_child);
    if (!L->left_child && !L->right_child)
      printf("%c", L->data);
    print_leaves(L->right_child);
  }
}

void print_left_only(tree_pointer L) {       /* Q7 */
  if (!L) return;
  if (L->left_child && !L->right_child)
    printf("%c", L->data);
  print_left_only(L->left_child);
  print_left_only(L->right_child);
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
    tree_pointer t = new_node('A',
               new_node('B', NULL,
                     new_node('C',
                           new_node('D', new_node('G', NULL, NULL),
                                         new_node('H', NULL, NULL)),
                           new_node('E', NULL,
                                 new_node('I', new_node('J', NULL, NULL),
                                               new_node('K', NULL, NULL))))),
               new_node('F', new_node('L', NULL, NULL), NULL));

    printf("print_leaves    : ");
    print_leaves(t);
    printf("\nprint_left_only : ");
    print_left_only(t);
    printf("\n");
    tree_free(t);
    return 0;
}

/* Expected output:
 * print_leaves    : GHJKL
 * print_left_only : F
 */
