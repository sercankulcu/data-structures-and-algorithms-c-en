/* AVL tree: every node keeps its subtree height (ht), the balance factor,
 * right/left rotations, and avl_insert, which fixes the LL, RR, LR and RL
 * cases. Examples from the notes: 30, 20, 40, 10, 25, 5 (inserting 5 gives
 * LL at 30, rot_right(30)); Weiss's sequence 3, 2, 1, 4, 5, 6, 7, 16, 15
 * (Table 11.9); the exercise 10, 20, 30, 25, 28 (RR, then LR).
 * Slides: "AVL Tree", "rot_right(): Two Pointers in the LL Case",
 * "AVL Insertion: BST Insertion + Rebalancing on the Way Back". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* not on the slides: the macro given in the notes */

typedef struct avl *avl_ptr;
struct avl {
    int      data;
    int      ht;        /* subtree height */
    avl_ptr left, right;
};
int ht(avl_ptr t) { return t ? t->ht : 0; }
int balance(avl_ptr t) {
    return ht(t->left) - ht(t->right);
}

avl_ptr rot_right(avl_ptr k2) {  // LL
  avl_ptr k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->ht = 1 + MAX(ht(k2->left), ht(k2->right));
  k1->ht = 1 + MAX(ht(k1->left), k2->ht);
  return k1;                       // new root
}

/* not on the slides: the left rotation and new_avl (the versions in the lecture notes) */
avl_ptr rot_left(avl_ptr k1) {  // RR
  avl_ptr k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->ht = 1 + MAX(ht(k1->left), ht(k1->right));
  k2->ht = 1 + MAX(k1->ht, ht(k2->right));
  return k2;                       // new root
}
avl_ptr new_avl(int x) {
  avl_ptr t = malloc(sizeof *t);
  if (!t) { fprintf(stderr, "Out of memory\n"); exit(EXIT_FAILURE); }
  t->data = x; t->ht = 1;
  t->left = t->right = NULL;
  return t;
}

avl_ptr avl_insert(avl_ptr t, int x) {
  if (!t) return new_avl(x);              /* malloc, ht = 1         */
  if (x < t->data)      t->left = avl_insert(t->left, x);
  else if (x > t->data) t->right = avl_insert(t->right, x);
  else return t;                           /* no duplicate keys      */
  t->ht = 1 + MAX(ht(t->left), ht(t->right));
  int d = balance(t);
  if (d >  1 && x < t->left->data) return rot_right(t);            /* LL */
  if (d < -1 && x > t->right->data) return rot_left(t);            /* RR */
  if (d >  1) { t->left = rot_left(t->left); return rot_right(t); } /* LR */
  if (d < -1) { t->right = rot_right(t->right); return rot_left(t); } /* RL */
  return t;
}

/* not on the slides: prints the tree as root(left, right), "-" for an empty subtree */
static void show(avl_ptr t) {
    if (!t) { printf("-"); return; }
    printf("%d", t->data);
    if (t->left || t->right) {
        printf("(");
        show(t->left);
        printf(", ");
        show(t->right);
        printf(")");
    }
}

/* not on the slides: gives the tree back to memory */
static void avl_free(avl_ptr t) {
    if (t) {
        avl_free(t->left);
        avl_free(t->right);
        free(t);
    }
}

/* not on the slides: inserts the values in order and prints the tree at each step */
static void insert_all(const int a[], int n) {
    avl_ptr root = NULL;
    for (int i = 0; i < n; i++) {
        root = avl_insert(root, a[i]);
        printf("+%d: ", a[i]);
        show(root);
        printf("\n");
    }
    printf("height = %d, balance at root = %d\n", ht(root), balance(root));
    avl_free(root);
}

int main(void)
{
    int a[] = {30, 20, 40, 10, 25, 5};
    int b[] = {3, 2, 1, 4, 5, 6, 7, 16, 15};
    int c[] = {10, 20, 30, 25, 28};
    insert_all(a, 6);
    insert_all(b, 9);
    insert_all(c, 5);
    return 0;
}

/* Expected output:
 * +30: 30
 * +20: 30(20, -)
 * +40: 30(20, 40)
 * +10: 30(20(10, -), 40)
 * +25: 30(20(10, 25), 40)
 * +5: 20(10(5, -), 30(25, 40))
 * height = 3, balance at root = 0
 * +3: 3
 * +2: 3(2, -)
 * +1: 2(1, 3)
 * +4: 2(1, 3(-, 4))
 * +5: 2(1, 4(3, 5))
 * +6: 4(2(1, 3), 5(-, 6))
 * +7: 4(2(1, 3), 6(5, 7))
 * +16: 4(2(1, 3), 6(5, 7(-, 16)))
 * +15: 4(2(1, 3), 6(5, 15(7, 16)))
 * height = 4, balance at root = -1
 * +10: 10
 * +20: 10(-, 20)
 * +30: 20(10, 30)
 * +25: 20(10, 30(25, -))
 * +28: 20(10, 28(25, 30))
 * height = 3, balance at root = -1
 */
