/* Walking through an array of structs: the average of the students' grade
 * point averages. Slide: "class_avg() Step by Step". Example from the
 * notes: Ada 3.2, Can 2.6, Ece 3.5 -> 3.10. */
#include <stdio.h>

typedef struct {
  int id;
  char name[16];
  double avg;
} Student;

double class_avg(const Student s[], int n) {
  double sum = 0.0;
  int i;
  for (i = 0; i < n; i++)
    sum += s[i].avg;               /* field via . */
  return n > 0 ? sum / n : 0.0;    /* empty class */
}

int main(void) {  /* not on the slides */
  Student s[] = {
    {101, "Ada", 3.2},
    {102, "Can", 2.6},
    {103, "Ece", 3.5},
  };
  printf("%.2f\n", class_avg(s, 3));
  printf("%.2f\n", class_avg(s, 0));   /* empty class */
  return 0;
}

/* Expected output:
 * 3.10
 * 0.00
 */
