/* Array representation of a binary tree: nodes are placed in cells that
 * start at 1; the parent is at i/2, the left child at 2i, the right child
 * at 2i+1 (if the index exceeds n there is no child). Example: the letters
 * A-J in cells 1-10, a complete tree.
 * Slide: "Representing a Binary Tree in an Array". */
#include <stdio.h>

#define MAX_NODES 63   /* 2^k - 1 */
char tree[MAX_NODES + 1];  /* [0] unused */
int  n;                    /* node count */

int parent(int i)      { return i / 2; }
int left_child(int i)  { return 2 * i; }
int right_child(int i) { return 2 * i + 1; }
/* has a child?  left_child(i) <= n */

/* not on the slides: the node in cell j, or '-' if there is none */
static char cell(int j)
{
    return (j >= 1 && j <= n) ? tree[j] : '-';
}

int main(void)
{
    const char *letters = "ABCDEFGHIJ";
    int i;

    n = 10;
    for (i = 1; i <= n; i++)
        tree[i] = letters[i - 1];

    printf(" i tree parent left right\n");
    for (i = 1; i <= n; i++)
        printf("%2d    %c      %c    %c     %c\n", i, tree[i],
               cell(parent(i)), cell(left_child(i)), cell(right_child(i)));
    return 0;
}

/* Expected output:
 *  i tree parent left right
 *  1    A      -    B     C
 *  2    B      A    D     E
 *  3    C      A    F     G
 *  4    D      B    H     I
 *  5    E      B    J     -
 *  6    F      C    -     -
 *  7    G      C    -     -
 *  8    H      D    -     -
 *  9    I      D    -     -
 * 10    J      E    -     -
 */
