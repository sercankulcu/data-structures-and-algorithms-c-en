/* Level-order traversal: node addresses are put in a circular array
 * queue; the node taken from the queue is printed and its existing
 * children are added at the rear. Examples: the A...H tree, the A...L tree
 * and the empty tree.
 * Slides: "Method II: Level-Order Traversal with a Queue",
 * "Level by Level with a Queue: A B C D E F G H". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

#define MAX_SIZE 100  /* not on the slides */

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

void enqueue(int front, int *rear,
             tree_pointer p, tree_pointer q[]) {
  *rear = (*rear + 1) % MAX_SIZE;
  if (*rear == front) {          /* full */
    fprintf(stderr, "Queue is full\n");
    exit(EXIT_FAILURE);
  }
  q[*rear] = p;
}
tree_pointer dequeue(int *front, int rear,
                     tree_pointer q[]) {
  if (*front == rear) return NULL; /* empty */
  *front = (*front + 1) % MAX_SIZE;
  return q[*front];
}

void level_order(tree_pointer L) {
  tree_pointer queue[MAX_SIZE];
  int front = 0, rear = 0;
  if (!L) return;              // tree may be empty
  enqueue(front, &rear, L, queue);
  while ((L = dequeue(&front, rear, queue))) {
    printf("%c", L->data);
    if (L->left_child)
      enqueue(front, &rear, L->left_child, queue);
    if (L->right_child)
      enqueue(front, &rear, L->right_child, queue);
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

int main(void)
{
    /* A...H: A(B(D(H), E), C(F, G)) */
    tree_pointer t1 = new_node('A',
                         new_node('B', new_node('D', new_node('H', NULL, NULL), NULL),
                                       new_node('E', NULL, NULL)),
                         new_node('C', new_node('F', NULL, NULL), new_node('G', NULL, NULL)));
    /* the A...L tree */
    tree_pointer t2 = new_node('A',
               new_node('B', NULL,
                     new_node('C',
                           new_node('D', new_node('G', NULL, NULL),
                                         new_node('H', NULL, NULL)),
                           new_node('E', NULL,
                                 new_node('I', new_node('J', NULL, NULL),
                                               new_node('K', NULL, NULL))))),
               new_node('F', new_node('L', NULL, NULL), NULL));

    printf("A...H     : [");
    level_order(t1);
    printf("]\nA...L     : [");
    level_order(t2);
    printf("]\nempty tree: [");
    level_order(NULL);
    printf("]\n");
    tree_free(t1);
    tree_free(t2);
    return 0;
}

/* Expected output:
 * A...H     : [ABCDEFGH]
 * A...L     : [ABFCLDEGHIJK]
 * empty tree: []
 */
