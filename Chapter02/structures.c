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
} person;

typedef struct {
  int day, month, year;
} date;

typedef struct {
  char name[10];
  date birth;             /* nested struct */
} member;

typedef struct list {
  char data;
  struct list *link;    /* self-reference */
} list;

typedef struct {
  enum { FEMALE, MALE } kind;   /* tag */
  union {
    int children;              /* if FEMALE */
    int beard;                 /* if MALE */
  } u;
} gender;

int main(void) {  /* not on the slides */
  /* the "struct" slide */
  person p1, p2;
  memset(&p1, 0, sizeof p1);   /* not on the slides: zero everything, padding bytes included */
  strcpy(p1.name, "Ali");
  p1.age = 21;
  p1.salary = 3500.0f;
  p2 = p1;          /* copied field by field */
  /* if (p1 == p2) -> DOES NOT COMPILE */
  printf("p2: %s %d %.1f\n", p2.name, p2.age, p2.salary);

  /* the "Nested and Self-Referential" slide */
  {
    member m;
    list a1, a2, a3, *q;
    strcpy(m.name, "Ayse");
    m.birth.day = 12; m.birth.month = 5;
    m.birth.year = 2004;
    printf("m: %s %d.%d.%d\n", m.name, m.birth.day, m.birth.month, m.birth.year);

    a1.data = 'a'; a1.link = &a2;
    a2.data = 'b'; a2.link = &a3;
    a3.data = 'c'; a3.link = NULL;
    printf("list:");
    for (q = &a1; q != NULL; q = q->link) printf(" %c", q->data);
    printf("\n");
  }

  /* the "union and Alignment" slide */
  {
    gender c;
    c.kind = MALE;
    c.u.beard = 0;   /* read only the field the tag allows */
    if (c.kind == MALE) printf("MALE, beard = %d\n", c.u.beard);
    else printf("FEMALE, children = %d\n", c.u.children);
  }

  printf("sizeof: person %zu, member %zu, list %zu\n",
         sizeof(person), sizeof(member), sizeof(list));
  return 0;
}

/* Expected output:
 * p2: Ali 21 3500.0
 * m: Ayse 12.5.2004
 * list: a b c
 * MALE, beard = 0
 * sizeof: person 20, member 24, list 16
 */
