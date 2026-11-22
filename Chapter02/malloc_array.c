/* An array whose size is known only at run time, made with malloc: NULL
 * check, use like an array, free, and setting the dangling pointer to
 * NULL. Slide: "Array with malloc". */
#include <stdio.h>
#include <stdlib.h>

int main(void) {  /* not on the slides */
  int n, i, *a;
  /* on the slides: scanf("%d", &n); there is no keyboard input here, n is a constant */
  n = 5;
  a = malloc(n * sizeof *a);   /* n ints */
  if (a == NULL) {
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < n; i++)
    a[i] = i * i;              /* like an array */
  for (i = 0; i < n; i++)      /* not on the slides: print the contents */
    printf("%d ", a[i]);
  printf("\n");                /* not on the slides */
  free(a);                     /* give it back */
  a = NULL;          /* no dangling pointer */
  printf("a = %s\n", a == NULL ? "NULL" : "?");  /* not on the slides */
  return 0;
}

/* Expected output:
 * 0 1 4 9 16
 * a = NULL
 */
