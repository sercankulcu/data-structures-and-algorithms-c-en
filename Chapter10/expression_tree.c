/* Expression tree: numbers are in the leaves, operators in the internal
 * nodes. eval uses a postorder walk: it first computes the two
 * subexpressions, then the operation at the root.
 * Examples: (8 / 4) * 3 + 5 and (A + B) * (C - D) for A = 7, B = 3, C = 9,
 * D = 4.
 * Slides: "Evaluating an Expression Tree: postorder Traversal", "eval(): (8 / 4) * 3 + 5 = 11". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

typedef struct expr *expr_pointer;
struct expr {
    char         op;      /* '+', '-', '*', '/' */
    int          value;   /* leaves only */
    expr_pointer left, right;
};

int eval(expr_pointer t) {
  if (!t->left && !t->right)      /* leaf: a number */
    return t->value;
  int a = eval(t->left);
  int b = eval(t->right);
  switch (t->op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    default:  return a / b;
  }
}

/* not on the slides: helpers that build and free a tree */
static expr_pointer new_expr(char op, int value, expr_pointer left, expr_pointer right)
{
    expr_pointer p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    p->op = op;
    p->value = value;
    p->left = left;
    p->right = right;
    return p;
}

static expr_pointer num(int v) { return new_expr(0, v, NULL, NULL); }
static expr_pointer opr(char c, expr_pointer left, expr_pointer right) { return new_expr(c, 0, left, right); }

static void expr_free(expr_pointer t)
{
    if (t) {
        expr_free(t->left);
        expr_free(t->right);
        free(t);
    }
}

int main(void)
{
    expr_pointer t1 = opr('+', opr('*', opr('/', num(8), num(4)), num(3)), num(5));
    expr_pointer t2 = opr('*', opr('+', num(7), num(3)), opr('-', num(9), num(4)));

    printf("(8 / 4) * 3 + 5 = %d\n", eval(t1));
    printf("(7 + 3) * (9 - 4) = %d\n", eval(t2));
    expr_free(t1);
    expr_free(t2);
    return 0;
}

/* Expected output:
 * (8 / 4) * 3 + 5 = 11
 * (7 + 3) * (9 - 4) = 50
 */
