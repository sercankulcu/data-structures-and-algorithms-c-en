/* Converting infix to postfix: operators get an in-stack priority (isp)
 * and an incoming priority (icp); a '#' sentinel sits at the bottom of the
 * stack.
 * Slides: "Code Trace: a*(b+c)-d -> Postfix", "Code Trace: The a*(b+c)*d Example". */
#include <stdio.h>
#include <ctype.h>    /* not on the slides: isalnum */

#define MAX 100       /* not on the slides */

/* not on the slides: isp and icp (as in the lecture notes) */
int isp(char c) {           /* in-stack priority */
  switch (c) {
    case '(': return 0;
    case '*': case '/': case '%': return 13;
    case '+': case '-': return 12;
    default: return -1;     /* '#': bottom of the stack */
  }
}
int icp(char c) {           /* incoming priority */
  if (c == '(') return 20;
  return isp(c);
}

void postfix(const char *e, char *out) {
  char y[MAX] = {'#'};  int top = 0, k = 0;
  for (; *e; e++) {
    if (isalnum(*e)) out[k++] = *e;
    else if (*e == ')') {
      while (y[top] != '(')
        out[k++] = y[top--];
      top--;                /* drop '(' */
    } else {
      while (isp(y[top]) >= icp(*e))
        out[k++] = y[top--];
      y[++top] = *e;
    }
  }
  while (top > 0) out[k++] = y[top--];
  out[k] = '\0';
}

int main(void)
{
    const char *expressions[] = {
        "a*(b+c)-d",
        "a*(b+c)*d",
        "a+b*c",
        "a/b-c+d*e-a*c",
        "a-b-c",
    };
    char out[MAX];
    int i;

    for (i = 0; i < 5; i++) {
        postfix(expressions[i], out);
        printf("%s -> %s\n", expressions[i], out);
    }
    return 0;
}

/* Expected output:
 * a*(b+c)-d -> abc+*d-
 * a*(b+c)*d -> abc+*d*
 * a+b*c -> abc*+
 * a/b-c+d*e-a*c -> ab/c-de*+ac*-
 * a-b-c -> ab-c-
 */
