/* Subset generation (the simplest backtracking): for each element first
 * the "take" and then the "skip" decision; 2^n subsets.
 * Slide: "Subset Generation Step by Step". Example: {a, b, c}. */
#include <stdio.h>  /* not on the slides */

void subset(char *s, int n, int i,
            int pick[]) {
  int j;
  if (i == n) {                  /* all decided */
    printf("{");
    for (j = 0; j < n; j++)
      if (pick[j]) printf("%c", s[j]);
    printf("}\n");
    return;
  }
  pick[i] = 1; subset(s, n, i + 1, pick);
  pick[i] = 0; subset(s, n, i + 1, pick);
}

int main(void) {  /* not on the slides */
  char s[] = "abc";
  int pick[3];
  subset(s, 3, 0, pick);
  return 0;
}

/* Expected output:
 * {abc}
 * {ab}
 * {ac}
 * {a}
 * {bc}
 * {b}
 * {c}
 * {}
 */
