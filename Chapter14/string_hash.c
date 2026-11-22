/* String hashing: the polynomial (Horner) hash takes the modulus at every
 * step; djb2 (Bernstein) computes h * 33 + c without a modulus and lets it
 * overflow. unsigned long is 32 bits on Windows and 64 bits on Linux, so
 * to make the output identical everywhere the low 32 bits of the djb2
 * result are printed.
 * Examples from the notes: str_hash("kedi", 11) = 3 (Table 14.5); the
 * anagrams "abc"/"cba", "ab"/"ba" (Table 14.4); djb2("kedi") low 32 bits
 * 2090432258.
 * Slides: "String hash" (two slides), "Trace: str_hash". */
#include <stdio.h>

unsigned str_hash(const char *s, unsigned m) {
  unsigned h = 0;
  for (; *s != '\0'; s++)
    h = (h * 31 + (unsigned char)*s) % m;
  return h;
}

unsigned long djb2(const char *s) {  /* Bernstein */
  unsigned long h = 5381;
  int c;
  while ((c = (unsigned char)*s++) != 0)
    h = h * 33 + c;
  return h;       /* then: h % m */
}

int main(void)
{
    const char *d[] = {"kedi", "abc", "cba", "ab", "ba"};
    for (int i = 0; i < 5; i++)
        printf("str_hash(\"%s\", 11) = %u\n", d[i], str_hash(d[i], 11));
    printf("djb2(\"ab\") = %lu\n", djb2("ab"));
    printf("djb2(\"abc\") = %lu\n", djb2("abc"));
    printf("djb2(\"kedi\") low 32 bits = %lu\n", djb2("kedi") & 0xFFFFFFFFUL);
    return 0;
}

/* Expected output:
 * str_hash("kedi", 11) = 3
 * str_hash("abc", 11) = 5
 * str_hash("cba", 11) = 0
 * str_hash("ab", 11) = 3
 * str_hash("ba", 11) = 0
 * djb2("ab") = 5863208
 * djb2("abc") = 193485963
 * djb2("kedi") low 32 bits = 2090432258
 */
