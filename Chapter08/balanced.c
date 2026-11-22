/* Parenthesis checking: opening brackets are pushed on a stack; when a
 * closing bracket comes, it must match the one on top; at the end the
 * stack must be empty.
 * Examples: one balanced string and three kinds of error (wrong match,
 * extra closing bracket, unclosed opening bracket).
 * Slide: "Code Trace: Balanced Brackets {a*(b+c)-[d]}". */
#include <stdio.h>
#include <stdbool.h>  /* not on the slides: bool */

#define MAX 100       /* not on the slides */

/* not on the slides: matches (as in the lecture notes) */
bool matches(char open, char close) {
  return (open == '(' && close == ')') ||
         (open == '[' && close == ']') ||
         (open == '{' && close == '}');
}

bool balanced(const char *e) {
  char y[MAX];  int top = -1;
  for (; *e; e++) {
    if (*e=='(' || *e=='[' || *e=='{')
      y[++top] = *e;
    else if (*e==')' || *e==']' || *e=='}') {
      if (top < 0 || !matches(y[top], *e))
        return false;  /* extra/wrong */
      top--;
    }
  }
  return top == -1;       /* none left open? */
}

int main(void)
{
    const char *strings[] = { "{a*(b+c)-[d]}", "[(a+b]*c)", "(a+b))", "((a+b)" };
    int i;

    for (i = 0; i < 4; i++)
        printf("%-14s %s\n", strings[i], balanced(strings[i]) ? "balanced" : "unbalanced");
    return 0;
}

/* Expected output:
 * {a*(b+c)-[d]}  balanced
 * [(a+b]*c)      unbalanced
 * (a+b))         unbalanced
 * ((a+b)         unbalanced
 */
