/* Linked-list representation and multiplication of polynomials. The terms
 * sit in nodes in decreasing order of exponent. new_term links a new node
 * after prev, delete_next_term deletes the node after prev; place_term puts a
 * product term in its place (if the exponent exists it adds the coefficients,
 * and deletes the node if the sum is 0); poly_mult starts each search at the
 * head of the previous row.
 * Examples from the notes: (x + 1)(x - 1) = x^2 - 1 and
 * (x^2 + 1)(x^2 - 1) = x^4 - 1.
 * Slides: "Polynomial Lists", "Adding / Deleting a Term", "poly_mult Code",
 * "poly_mult() Step by Step". */
#include <stdio.h>
#include <stdlib.h>

typedef struct poly_node *poly_pointer;
typedef struct poly_node {
  int coef;
  int expon;
  poly_pointer link;
} poly_node;

/* make a term; link it after prev if given */
poly_pointer new_term(int expon, int coef,
                           poly_pointer prev) {
  poly_pointer p = malloc(sizeof *p);
  if (!p) { printf("Out of memory!\n"); exit(1); }
  p->expon = expon;  p->coef = coef;
  if (prev) {              /* middle or end */
    p->link = prev->link;    /* new node first */
    prev->link = p;         /* then prev */
  } else p->link = NULL;      /* stands alone */
  return p;
}

/* delete the node after prev */
void delete_next_term(
        poly_pointer prev) {
  poly_pointer victim =
        prev->link;
  if (!victim) return;
  prev->link =
        victim->link;
  free(victim);
}

poly_pointer place_term(poly_pointer r,
                       int expon, int coef) {
  while (r->link && r->link->expon > expon) r = r->link;
  if (!r->link || r->link->expon < expon)
    new_term(expon, coef, r);         /* new exponent */
  else if ((r->link->coef += coef) == 0)
    delete_next_term(r);               /* became 0 */
  return r;
}

poly_pointer poly_mult(poly_pointer pstart,
                     poly_pointer qstart) {
  poly_pointer p, q, r = NULL, start = NULL, rstart=NULL;
  for (p = pstart; p; p = p->link) {
    r = start;               /* search from here */
    for (q = qstart; q; q = q->link) {
      int expon = p->expon + q->expon;
      int coef = p->coef * q->coef;
      if (rstart) r = place_term(r, expon, coef);
      else rstart=r=start=new_term(expon, coef, NULL);
      if (q == qstart) start = r;  /* for next p */
    }
  }
  return rstart;
}

/* not on the slides: prints a polynomial */
static void print_terms(const char *name, poly_pointer p) {
  printf("%s =", name);
  for (poly_pointer t = p; t; t = t->link) {
    int k = t->coef;
    if (t == p) printf(" %dx^%d", k, t->expon);
    else printf(" %c %dx^%d", k < 0 ? '-' : '+', k < 0 ? -k : k, t->expon);
  }
  printf("\n");
}

/* not on the slides: frees the whole list */
static void free_poly(poly_pointer p) {
  while (p) {
    poly_pointer q = p->link;
    free(p);
    p = q;
  }
}

/* not on the slides: builds a two-term polynomial (exponent 1 > exponent 2) */
static poly_pointer two_terms(int k1, int u1, int k2, int u2) {
  poly_pointer start = new_term(u1, k1, NULL);
  new_term(u2, k2, start);
  return start;
}

int main(void)
{
  poly_pointer A = two_terms(1, 1, 1, 0);     /* x + 1 */
  poly_pointer B = two_terms(1, 1, -1, 0);    /* x - 1 */
  poly_pointer C = two_terms(1, 2, 1, 0);     /* x^2 + 1 */
  poly_pointer D = two_terms(1, 2, -1, 0);    /* x^2 - 1 */
  poly_pointer AB, CD;

  print_terms("A", A);
  print_terms("B", B);
  AB = poly_mult(A, B);
  print_terms("A*B", AB);
  print_terms("C", C);
  print_terms("D", D);
  CD = poly_mult(C, D);
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
