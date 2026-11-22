/* Linked-list representation and multiplication of polynomials. The terms
 * sit in nodes in decreasing order of exponent. add_term links a new node
 * after prev, delete_next deletes the node after prev; place puts a
 * product term in its place (if the exponent exists it adds the coefficients,
 * and deletes the node if the sum is 0); pmult_list starts each search at the
 * head of the previous row.
 * Examples from the notes: (x + 1)(x - 1) = x^2 - 1 and
 * (x^2 + 1)(x^2 - 1) = x^4 - 1.
 * Slides: "Storing a Polynomial as a Linked List", "Helpers: add_term and
 * delete_next" (two blocks), "Multiplying Two Polynomials Given as Lists",
 * "pmult_list: (x + 1)(x - 1)". */
#include <stdio.h>
#include <stdlib.h>

typedef struct poly_node *poly_ptr;
typedef struct poly_node {
  int coef;
  int expon;
  poly_ptr link;
} poly_node;

/* make a term; link it after prev if given */
poly_ptr add_term(int expon, int coef,
                           poly_ptr prev) {
  poly_ptr p = malloc(sizeof *p);
  if (!p) { printf("Out of memory!\n"); exit(1); }
  p->expon = expon;  p->coef = coef;
  if (prev) {              /* middle or end */
    p->link = prev->link;    /* new node first */
    prev->link = p;         /* then prev */
  } else p->link = NULL;      /* stands alone */
  return p;
}

/* delete the node after prev */
void delete_next(
        poly_ptr prev) {
  poly_ptr victim =
        prev->link;
  if (!victim) return;
  prev->link =
        victim->link;
  free(victim);
}

poly_ptr place(poly_ptr r,
                       int expon, int coef) {
  while (r->link && r->link->expon > expon) r = r->link;
  if (!r->link || r->link->expon < expon)
    add_term(expon, coef, r);         /* new exponent */
  else if ((r->link->coef += coef) == 0)
    delete_next(r);               /* became 0 */
  return r;
}

poly_ptr pmult_list(poly_ptr p_head,
                     poly_ptr q_head) {
  poly_ptr p, q, r = NULL, anchor = NULL, r_head=NULL;
  for (p = p_head; p; p = p->link) {
    r = anchor;               /* search from here */
    for (q = q_head; q; q = q->link) {
      int expon = p->expon + q->expon;
      int coef = p->coef * q->coef;
      if (r_head) r = place(r, expon, coef);
      else r_head=r=anchor=add_term(expon, coef, NULL);
      if (q == q_head) anchor = r;  /* for next p */
    }
  }
  return r_head;
}

/* not on the slides: prints a polynomial */
static void print_terms(const char *name, poly_ptr p) {
  printf("%s =", name);
  for (poly_ptr t = p; t; t = t->link) {
    int k = t->coef;
    if (t == p) printf(" %dx^%d", k, t->expon);
    else printf(" %c %dx^%d", k < 0 ? '-' : '+', k < 0 ? -k : k, t->expon);
  }
  printf("\n");
}

/* not on the slides: frees the whole list */
static void free_poly(poly_ptr p) {
  while (p) {
    poly_ptr q = p->link;
    free(p);
    p = q;
  }
}

/* not on the slides: builds a two-term polynomial (exponent 1 > exponent 2) */
static poly_ptr two_terms(int k1, int u1, int k2, int u2) {
  poly_ptr start = add_term(u1, k1, NULL);
  add_term(u2, k2, start);
  return start;
}

int main(void)
{
  poly_ptr A = two_terms(1, 1, 1, 0);     /* x + 1 */
  poly_ptr B = two_terms(1, 1, -1, 0);    /* x - 1 */
  poly_ptr C = two_terms(1, 2, 1, 0);     /* x^2 + 1 */
  poly_ptr D = two_terms(1, 2, -1, 0);    /* x^2 - 1 */
  poly_ptr AB, CD;

  print_terms("A", A);
  print_terms("B", B);
  AB = pmult_list(A, B);
  print_terms("A*B", AB);
  print_terms("C", C);
  print_terms("D", D);
  CD = pmult_list(C, D);
  print_terms("C*D", CD);

  free_poly(A); free_poly(B); free_poly(C); free_poly(D);
  free_poly(AB); free_poly(CD);
  return 0;
}

/* Expected output:
 * A = 1x^1 + 1x^0
 * B = 1x^1 - 1x^0
 * A*B = 1x^2 - 1x^0
 * C = 1x^2 + 1x^0
 * D = 1x^2 - 1x^0
 * C*D = 1x^4 - 1x^0
 */
