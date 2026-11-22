/* From a general tree to a binary tree: the left child - right sibling
 * representation. Every node points to its first child and to the sibling
 * on its right; the structure is the same as a binary tree node. Example
 * tree A(B(E(K,L),F),C(G),D(H(M),I,J)). The preorder of the binary tree
 * equals the preorder of the general tree, and the inorder of the binary
 * tree equals the postorder of the general tree.
 * Slide: "Turning a General Tree into a Binary Tree: Left Child, Right Sibling". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

struct gnode {
    char data;
    struct gnode *child;      /* = left */
    struct gnode *sibling;    /* = right */
};

/* not on the slides: building, traversing and freeing nodes */
static struct gnode *gn(char data, struct gnode *child, struct gnode *sibling)
{
    struct gnode *p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    p->data = data;
    p->child = child;
    p->sibling = sibling;
    return p;
}

static void preorder(const struct gnode *L)     /* like a binary tree: V-left-right */
{
    if (L) {
        printf("%c", L->data);
        preorder(L->child);
        preorder(L->sibling);
    }
}

static void inorder(const struct gnode *L)      /* like a binary tree: left-V-right */
{
    if (L) {
        inorder(L->child);
        printf("%c", L->data);
        inorder(L->sibling);
    }
}

static void gfree(struct gnode *L)
{
    if (L) {
        gfree(L->child);
        gfree(L->sibling);
        free(L);
    }
}

int main(void)
{
    struct gnode *D, *C, *B, *A;

    D = gn('D', gn('H', gn('M', NULL, NULL), gn('I', NULL, gn('J', NULL, NULL))), NULL);
    C = gn('C', gn('G', NULL, NULL), D);
    B = gn('B', gn('E', gn('K', NULL, gn('L', NULL, NULL)), gn('F', NULL, NULL)), C);
    A = gn('A', B, NULL);                /* the root has no sibling: right link is NULL */

    printf("preorder : ");
    preorder(A);
    printf("\ninorder  : ");
    inorder(A);
    printf("\n");
    gfree(A);
    return 0;
}

/* Expected output:
 * preorder : ABEKLFCGDHMIJ
 * inorder  : KLEFBGCMHIJDA
 */
