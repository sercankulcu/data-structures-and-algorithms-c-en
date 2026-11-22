/* struct, nested and self-referential structures, tagged union.
 * Structure assignment copies field by field; comparing with == does not
 * compile. Slides: "struct", "Nested and Self-Referential",
 * "union and Alignment". The sizeof values are for 64-bit Linux (same as
 * the driver in the notes). */
#include <stdio.h>
#include <string.h>  /* not on the slides: for strcpy */

typedef struct {
  char name[10];
  int age;
  float salary;
} human;

typedef struct {
  int day, month, year;
} date;

typedef struct {
  char name[10];
  date dob;             /* nested struct */
} person;

typedef struct list {
  char data;
  struct list *link;    /* self-reference */
} list;

typedef struct {
  enum { FEMALE, MALE } sex;   /* tag */
  union {
    int children;              /* if FEMALE */
    int beard;                 /* if MALE */
  } u;
} sex_type;

int main(void) {  /* not on the slides */
  /* the "struct" slide */
  human h1, h2;
  memset(&h1, 0, sizeof h1);   /* not on the slides: zero everything, padding bytes included */
  strcpy(h1.name, "Ali");
  h1.age = 21;
  h1.salary = 3500.0f;
  h2 = h1;          /* copied field by field */
  /* if (h1 == h2) -> DOES NOT COMPILE */
  printf("h2: %s %d %.1f\n", h2.name, h2.age, h2.salary);

  /* the "Nested and Self-Referential" slide */
  {
    person p;
    list a1, a2, a3, *q;
    strcpy(p.name, "Ayse");
    p.dob.day = 12; p.dob.month = 5;
    p.dob.year = 2004;
    printf("p: %s %d.%d.%d\n", p.name, p.dob.day, p.dob.month, p.dob.year);

    a1.data = 'a'; a1.link = &a2;
    a2.data = 'b'; a2.link = &a3;
    a3.data = 'c'; a3.link = NULL;
    printf("list:");
    for (q = &a1; q != NULL; q = q->link) printf(" %c", q->data);
    printf("\n");
  }

  /* the "union and Alignment" slide */
  {
    sex_type s;
    s.sex = MALE;
    s.u.beard = 0;   /* read only the field the tag allows */
    if (s.sex == MALE) printf("MALE, beard = %d\n", s.u.beard);
    else printf("FEMALE, children = %d\n", s.u.children);
  }

  printf("sizeof: human %zu, person %zu, list %zu\n",
         sizeof(human), sizeof(person), sizeof(list));
  return 0;
}

/* Expected output:
 * h2: Ali 21 3500.0
 * p: Ayse 12.5.2004
 * list: a b c
 * MALE, beard = 0
 * sizeof: human 20, person 24, list 16
 */
