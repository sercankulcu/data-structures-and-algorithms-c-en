/* Program that uses the Fraction ADT only through its interface:
 * 1/2 + 1/3 = 5/6. Slide: "Using the Interface". The equality example
 * 2/4 = 1/2 from the notes is added at the end. */
/* main.c : knows only the interface */
#include "fraction.h"
#include <stddef.h> /* NULL */
#include <stdio.h>  /* not on the slides: for printf */
int main(void) {
  Fraction *a = fraction_create(1, 2);
  Fraction *b = fraction_create(1, 3);
  Fraction *s = NULL;
  if (a && b) s = fraction_add(a, b);
  if (s) fraction_print(s);  /* 5/6 */
  fraction_delete(a); fraction_delete(b);
  fraction_delete(s);  /* free(NULL) is safe */

  /* not on the slides: fraction_equal test (the 2/4 and 1/2 example from the notes) */
  {
    Fraction *c = fraction_create(2, 4);
    Fraction *d = fraction_create(1, 2);
    if (c && d) printf("2/4 == 1/2 ? %d\n", fraction_equal(c, d));
    fraction_delete(c); fraction_delete(d);
  }
  return 0;
}

/* Expected output:
 * 5/6
 * 2/4 == 1/2 ? 1
 */
