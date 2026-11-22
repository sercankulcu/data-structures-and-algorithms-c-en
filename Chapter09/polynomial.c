/* Representing a multivariate polynomial with a generalized list: every
 * level starts with a VAR node; the coefficient of a term is either an
 * integer (NO) or a sub-polynomial list (PTR). Examples: 3x^2y and
 * P(x,y,z) = ((x^10+2x^8)y^3 + 3x^8y^2)z^2 + ((x^4+6x^3)y^4 + 2y)z;
 * the values are computed at the point x = 2, y = 3, z = 1.
 * Slide: "Example: a Multivariate Polynomial". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: malloc, free, exit */

typedef enum { VAR, PTR, NO } tag_t;
typedef struct pnode *poly_pointer;
struct pnode {
    tag_t tag;              // three kinds
    union {
        char var;           // VAR: variable name
        poly_pointer dlink; // PTR: coef is a list
        int coef;           // NO : integer coef
    };
    int exp;                // exponent
    poly_pointer link;
};

/* not on the slides: value of the polynomial (as in the lecture notes) */
// P: list starting with a VAR node; d['x'-'x'], d['y'-'x'], d['z'-'x']: variable values
long poly_eval(poly_pointer P, const long d[]) {
    long sum = 0, v = d[P->var - 'x'];  // value of this level's variable
    long coef, power;
    int k;
    for (poly_pointer p = P->link; p; p = p->link) {
        coef = (p->tag == PTR) ? poly_eval(p->dlink, d)  // coefficient is a list
                               : p->coef;                // NO: integer
        for (power = 1, k = 0; k < p->exp; k++) power *= v;
        sum += coef * power;
    }
    return sum;
}

/* not on the slides: helpers that build, count and free nodes */
static poly_pointer new_pnode(tag_t t, int exp, poly_pointer link)
{
    poly_pointer p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    p->tag = t;
    p->exp = exp;
    p->link = link;
    return p;
}

static poly_pointer new_var(char var, poly_pointer link)
{
    poly_pointer p = new_pnode(VAR, 0, link);
    p->var = var;
    return p;
}

static poly_pointer new_no(int coef, int exp, poly_pointer link)
{
    poly_pointer p = new_pnode(NO, exp, link);
    p->coef = coef;
    return p;
}

static poly_pointer new_ptr(poly_pointer sub, int exp, poly_pointer link)
{
    poly_pointer p = new_pnode(PTR, exp, link);
    p->dlink = sub;
    return p;
}

static int poly_count(poly_pointer P)
{
    int s = 0;
    for (; P; P = P->link)
        s += 1 + (P->tag == PTR ? poly_count(P->dlink) : 0);
    return s;
}

static void poly_free(poly_pointer P)
{
    poly_pointer q;
    while (P) {
        if (P->tag == PTR) poly_free(P->dlink);
        q = P->link;
        free(P);
        P = q;
    }
}

int main(void)
{
    const long d[3] = { 2, 3, 1 };     /* x = 2, y = 3, z = 1 */
    poly_pointer T, X1, X2, X3, Y1, Y2, P;

    /* 3x^2y = (3x^2) y^1 */
    T = new_var('y', new_ptr(new_var('x', new_no(3, 2, NULL)), 1, NULL));

    X1 = new_var('x', new_no(1, 10, new_no(2, 8, NULL)));      /* x^10 + 2x^8 */
    X2 = new_var('x', new_no(3, 8, NULL));                     /* 3x^8 */
    X3 = new_var('x', new_no(1, 4, new_no(6, 3, NULL)));       /* x^4 + 6x^3 */
    Y1 = new_var('y', new_ptr(X1, 3, new_ptr(X2, 2, NULL)));
    Y2 = new_var('y', new_ptr(X3, 4, new_no(2, 1, NULL)));
    P  = new_var('z', new_ptr(Y1, 2, new_ptr(Y2, 1, NULL)));

    printf("3x^2y: %d nodes, value = %ld\n", poly_count(T), poly_eval(T, d));
    printf("P: %d nodes\n", poly_count(P));
    printf("coefficient of z^2 = %ld\n", poly_eval(Y1, d));
    printf("coefficient of z = %ld\n", poly_eval(Y2, d));
    printf("P(2, 3, 1) = %ld\n", poly_eval(P, d));

    poly_free(T);
    poly_free(P);
    return 0;
}

/* Expected output:
 * 3x^2y: 4 nodes, value = 36
 * P: 17 nodes
 * coefficient of z^2 = 48384
 * coefficient of z = 5190
 * P(2, 3, 1) = 53574
 */
