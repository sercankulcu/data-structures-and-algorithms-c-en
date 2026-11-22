/* What strlen does: a pointer is advanced up to '\0' and the length is the
 * pointer difference. Slide: "length() Step by Step". Example:
 * length("data"). */
#include <stdio.h>
#include <stddef.h>  /* not on the slides: size_t */

size_t length(const char *s) {
  const char *p = s;
  while (*p != '\0')     /* up to the terminator */
    p++;
  return (size_t)(p - s);  /* pointer difference */
}

int main(void) {  /* not on the slides */
  printf("%zu\n", length("data"));
  printf("%zu\n", length(""));
  return 0;
}

/* Expected output:
 * 4
 * 0
 */
