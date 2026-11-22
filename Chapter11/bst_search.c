/* Search in a binary search tree: the iterative bst_search, the recursive
 * search, the "does it work?" body from the slides (named search_body) and
 * search_rec, which does not use the ordering. Examples from the notes: in
 * the tree 47, 55, 49, 26, 34, 17, 52, 84, 93, 52, 34 and 60 are searched;
 * in a general tree with root 5, left child 9 (whose right child is 1) and
 * right child 2, 2, 1 and 7 are searched.
 * Slides: "bst_search(52, L) - Iterative", "Recursive Search: search(34, L)",
 * "Example: Does This Work?", "Sample Solution: Searching Any Binary Tree". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;
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

/* not on the slides: the routine from the slide "bst_insert() Step by Step",
   to build the tree */
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

tree_ptr bst_search(int x, tree_ptr L) {
  while (L) {           // pick a subtree
    if (x == L->data) return L;
    if (x < L->data) L = L->left;
    else             L = L->right;
  }
  return NULL;          // not found
}

tree_ptr search(int x, tree_ptr L) {
  if (!L) return NULL;          // absent
  if (x == L->data) return L;   // found
  if (x < L->data)
    return search(x, L->left);
  return search(x, L->right);
}

/* not on the slides: the routine header that wraps the body on the slide
   "The Trap in Recursive Search" */
tree_ptr search_body(int x, tree_ptr L) {
if (L) {
  if (x == L->data) return L;
  if (x <  L->data) return search_body(x, L->left);
  return search_body(x, L->right);
}
return NULL;   /* L == NULL: empty (sub)tree */
}

tree_ptr search_rec(int data, tree_ptr L) {
  if (!L) return NULL;              /* empty tree?   */
  if (L->data == data) return L;    /* key found     */
  tree_ptr T = search_rec(data, L->left);
  return T ? T : search_rec(data, L->right);
}

/* not on the slides: prints the result of a search */
static void report(const char *name, int x, tree_ptr p) {
    if (p) printf("%s(%d): found, data = %d\n", name, x, p->data);
    else   printf("%s(%d): absent\n", name, x);
}

/* not on the slides: allocates a single node */
static tree_ptr make_node(int x) {
    tree_ptr r = get_node();
    r->data = x;
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

int main(void)
{
    int order[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    tree_ptr L = NULL;
    for (int i = 0; i < 9; i++)
        bst_insert(order[i], &L);

    printf("Binary search tree:\n");
    report("bst_search", 52, bst_search(52, L));
    report("bst_search", 60, bst_search(60, L));
    report("search", 34, search(34, L));
    report("search", 60, search(60, L));
    report("search_body", 34, search_body(34, L));
    report("search_rec", 84, search_rec(84, L));

    /* general binary tree: 5(9(-, 1), 2) */
    tree_ptr G = make_node(5);
    G->left = make_node(9);
    G->left->right = make_node(1);
    G->right = make_node(2);

    printf("General binary tree:\n");
    report("search_body", 2, search_body(2, G));    /* goes left, misses 2 */
    report("search_rec", 2, search_rec(2, G));
    report("search_rec", 1, search_rec(1, G));
    report("search_rec", 7, search_rec(7, G));

    tree_free(L);
    tree_free(G);
    return 0;
}

/* Expected output:
 * Binary search tree:
 * bst_search(52): found, data = 52
 * bst_search(60): absent
 * search(34): found, data = 34
 * search(60): absent
 * search_body(34): found, data = 34
 * search_rec(84): found, data = 84
 * General binary tree:
 * search_body(2): absent
 * search_rec(2): found, data = 2
 * search_rec(1): found, data = 1
 * search_rec(7): absent
 */
