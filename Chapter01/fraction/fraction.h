/* Interface of the Fraction ADT: an opaque type and the declarations of
 * its operations. Slide: "Abstraction in C: the Header File". */
/* fraction.h : interface (WHAT?) */
#ifndef FRACTION_H
#define FRACTION_H
typedef struct fraction Fraction; /* opaque */

Fraction *fraction_create(int num, int den);
Fraction *fraction_add(const Fraction *a,
                       const Fraction *b);
int  fraction_equal(const Fraction *a,
                    const Fraction *b);
void fraction_print(const Fraction *f);
void fraction_free(Fraction *f);
#endif
