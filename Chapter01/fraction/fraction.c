/* Implementation of the Fraction ADT: struct fraction is defined only in
 * this file. Slides: "Abstraction in C: the Header File" (fraction_create)
 * and "Using the Interface" (fraction_add, fraction_equal, fraction_print,
 * fraction_free). */
/* fraction.c : implementation (HOW?) */
#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

struct fraction { int num, den; };

Fraction *fraction_create(int num, int den) {
  Fraction *f;
  if (den == 0) return NULL;
  f = malloc(sizeof *f);
  if (f == NULL) return NULL;
  f->num = num;
  f->den = den;
  return f;
}

Fraction *fraction_add(const Fraction *a,
                       const Fraction *b) {
  return fraction_create(
      a->num * b->den
        + b->num * a->den,
      a->den * b->den);
}
int fraction_equal(const Fraction *a,
                   const Fraction *b) {
  return a->num * b->den
      == b->num * a->den;
}
void fraction_print(const Fraction *f) {
  printf("%d/%d\n", f->num, f->den);
}
void fraction_free(Fraction *f) { free(f); }
