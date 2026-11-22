/* Representation 2 of a polynomial: the terms of all polynomials sit in one
 * array P, and a polynomial is the range P[start..finish]. padd adds two
 * polynomials like a merge and writes the result at the end of the array,
 * starting at avail.
 * Two examples from the notes: (4x^3 + 2x^2 + 5) + (3x^3 - 2x^2 + x) and
 * (3x^20 + 2x^5 + 4) + (x^5 + 10x^3 + 3x^2 + 1).
 * Slides: "Method 2 (Better): Only the Nonzero Terms", "Adding by Merging with
 * Two Pointers", "padd: A + B, Term by Term". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101   /* max number of terms */
typedef struct {
  float coef;            /* coefficient */
  int expon;             /* exponent */
} polynomial;
polynomial P[MAX_TERMS]; /* all polynomials here */
int avail = 0;           /* first free slot */

#define COMPARE(x, y) \
  ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)

void attach(float coef, int expon) {
  if (avail >= MAX_TERMS) {
    fprintf(stderr, "Too many terms!\n"); exit(1);
  }
  P[avail].coef = coef;
  P[avail++].expon = expon;
}
#define APPEND(k) attach(P[k].coef, P[k].expon)

void padd(int sa,int fa,int sb,int fb,int*sd,int*fd){
  float c; *sd = avail;               /* start of D */
  while (sa <= fa && sb <= fb)
    switch (COMPARE(P[sa].expon, P[sb].expon)) {
    case -1: APPEND(sb); sb++; break;     /* B larger */
    case  1: APPEND(sa); sa++; break;     /* A larger */
    case  0: c = P[sa].coef + P[sb].coef;
      if (c) attach(c, P[sa].expon); /* skip 0 */
      sa++; sb++;
    }
  for (; sa <= fa; sa++) APPEND(sa);      /* rest of A */
  for (; sb <= fb; sb++) APPEND(sb);      /* rest of B */
  *fd = avail - 1;
}

/* not on the slides: appends n terms with attach, returns the start */
static int load(const float c[], const int e[], int n) {
  int s = avail;
  for (int i = 0; i < n; i++) attach(c[i], e[i]);
  return s;
}

/* not on the slides: prints the polynomial P[s..f] */
static void print_terms(const char *name, int s, int f) {
  printf("%s =", name);
  for (int k = s; k <= f; k++) {
    float c = P[k].coef;
    if (k == s) printf(" %gx^%d", c, P[k].expon);
    else printf(" %c %gx^%d", c < 0 ? '-' : '+', c < 0 ? -c : c, P[k].expon);
  }
  printf("\n");
}

int main(void)
{
  float ac[] = {4, 2, 5};     int ae[] = {3, 2, 0};
  float bc[] = {3, -2, 1};    int be[] = {3, 2, 1};
  float a2c[] = {3, 2, 4};    int a2e[] = {20, 5, 0};
  float b2c[] = {1, 10, 3, 1}; int b2e[] = {5, 3, 2, 0};
  int sa, sb, sd, fd;

  sa = load(ac, ae, 3);                 /* P[0..2] */
  sb = load(bc, be, 3);                 /* P[3..5], avail = 6 */
  print_terms("A", sa, sa + 2);
  print_terms("B", sb, sb + 2);
  padd(sa, sa + 2, sb, sb + 2, &sd, &fd);
  print_terms("D", sd, fd);
  printf("sd = %d, fd = %d, avail = %d\n", sd, fd, avail);

  avail = 0;                             /* second example: the array is reused from the start */
  sa = load(a2c, a2e, 3);               /* P[0..2] */
  sb = load(b2c, b2e, 4);               /* P[3..6], avail = 7 */
  print_terms("A", sa, sa + 2);
  print_terms("B", sb, sb + 3);
  padd(sa, sa + 2, sb, sb + 3, &sd, &fd);
  print_terms("D", sd, fd);
  printf("sd = %d, fd = %d, avail = %d\n", sd, fd, avail);
  return 0;
}

/* Expected output:
 * A = 4x^3 + 2x^2 + 5x^0
 * B = 3x^3 - 2x^2 + 1x^1
 * D = 7x^3 + 1x^1 + 5x^0
 * sd = 6, fd = 8, avail = 9
 * A = 3x^20 + 2x^5 + 4x^0
 * B = 1x^5 + 10x^3 + 3x^2 + 1x^0
 * D = 3x^20 + 3x^5 + 10x^3 + 3x^2 + 5x^0
 * sd = 7, fd = 11, avail = 12
 */
