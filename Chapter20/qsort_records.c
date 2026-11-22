/* Sorting records (structs) with qsort: by_name sorts alphabetically,
 * by_grade_desc puts high grades first. The example is the five students from
 * the notes. qsort is not stable: by_grade_desc may change the order of
 * students with equal grades depending on the library, so only the grades are
 * printed after that sort. by_grade_then_name from the notes looks at the
 * name on a tie and gives the same result on every library.
 * Slide: "Sorting Records (Structs) with qsort". */
#include <stdio.h>   /* not on the slides */
#include <stdlib.h>  /* not on the slides: qsort */
#include <string.h>  /* not on the slides: strcmp */

typedef struct { char name[20]; int grade; } student;

int by_name(const void *p, const void *q) {
    const student *x = p, *y = q;
    return strcmp(x->name, y->name);    // alphabetical
}
int by_grade_desc(const void *p, const void *q) {
    const student *x = p, *y = q;
    return (y->grade > x->grade) - (y->grade < x->grade);
}
/* qsort(s, n, sizeof s[0], by_name); */

/* not on the slides: the comparison with a secondary key from the notes */
int by_grade_then_name(const void *p, const void *q) {
    const student *x = p, *y = q;
    int k = (y->grade > x->grade) - (y->grade < x->grade);
    if (k != 0) return k;               /* grades differ: higher first */
    return strcmp(x->name, y->name);    /* grades equal: alphabetical */
}

int main(void) {   /* not on the slides */
    student s[] = {
        {"Zeynep", 85}, {"Ali", 70}, {"Mehmet", 85}, {"Ayse", 92}, {"Can", 70}
    };
    size_t n = sizeof s / sizeof s[0];

    qsort(s, n, sizeof s[0], by_name);
    printf("by_name:");
    for (size_t i = 0; i < n; i++) printf(" %s %d", s[i].name, s[i].grade);
    printf("\n");

    qsort(s, n, sizeof s[0], by_grade_desc);
    printf("by_grade_desc (grades):");
    for (size_t i = 0; i < n; i++) printf(" %d", s[i].grade);
    printf("\n");

    qsort(s, n, sizeof s[0], by_grade_then_name);
    printf("by_grade_then_name:");
    for (size_t i = 0; i < n; i++) printf(" %s %d", s[i].name, s[i].grade);
    printf("\n");
    return 0;
}


/* Expected output:
 * by_name: Ali 70 Ayse 92 Can 70 Mehmet 85 Zeynep 85
 * by_grade_desc (grades): 92 85 85 70 70
 * by_grade_then_name: Ayse 92 Mehmet 85 Zeynep 85 Ali 70 Can 70
 */
