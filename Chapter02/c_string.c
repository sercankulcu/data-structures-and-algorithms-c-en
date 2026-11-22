/* A C string: a char array ending in '\0'. The difference between strlen
 * and sizeof, snprintf for a safe copy, strcmp to compare contents.
 * Slide: "String = char Array". */
#include <stdio.h>
#include <string.h>

int main(void) {  /* not on the slides */
  char s[] = "dog";      /* 4 bytes: d o g \0 */
  char t[10];
  char *p = "dog";       /* read-only literal */

  printf("strlen(s) = %zu\n", strlen(s));   /* 3 : up to \0 */
  printf("sizeof s = %zu\n", sizeof s);     /* 4 : size of the array */

  strcpy(t, s);                 /* is t big enough? */
  printf("t = %s\n", t);
  snprintf(t, sizeof t, "%s!", s);   /* safe */
  printf("t = %s\n", t);
  if (strcmp(s, "dog") == 0)         /* not ==! */
    printf("s has the same content as \"dog\"\n");
  printf("p = %s\n", p);
  return 0;
}

/* Expected output:
 * strlen(s) = 3
 * sizeof s = 4
 * t = dog
 * t = dog!
 * s has the same content as "dog"
 * p = dog
 */
