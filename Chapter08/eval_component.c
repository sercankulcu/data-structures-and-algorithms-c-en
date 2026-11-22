/* Evaluating a postfix expression, component version: the expression comes
 * as a parameter, the stack is a local array inside eval; there are no
 * global variables.
 * Slides: "From Globals to Parameters", "Code Trace: eval(\"23*54*+9-\")",
 * "Code Trace: Another Expression". */
#include <stdio.h>
#include <ctype.h>    /* not on the slides: isdigit */

#define MAX_SIZE 100  /* not on the slides */

/* component: all parameters/locals */
float eval(const char *expr);
/* the stack is a local array in eval */

float eval(const char *expr) {
  float y[MAX_SIZE], op1, op2;  int top = -1;
  for (int n = 0; expr[n] != '\0'; n++) {
    char c = expr[n];
    if (isdigit(c)) y[++top] = c - '0';
    else {
      op2 = y[top--];  op1 = y[top--];
      switch (c) {
        case '+': y[++top] = op1 + op2; break;
        case '-': y[++top] = op1 - op2; break;
        case '*': y[++top] = op1 * op2; break;
        case '/': y[++top] = op1 / op2; break;
      }
    }
  }
  return y[top];
}

int main(void)
{
    /* in main: */
    float a = eval("23*54*+9-");
    float b = eval("42/2-33*+42*-");
    float c = eval("623+-382/+*");   /* not on the slides: the exercise expression in the notes */

    printf("eval(\"23*54*+9-\") = %g\n", a);
    printf("eval(\"42/2-33*+42*-\") = %g\n", b);
    printf("eval(\"623+-382/+*\") = %g\n", c);
    return 0;
}

/* Expected output:
 * eval("23*54*+9-") = 17
 * eval("42/2-33*+42*-") = 1
 * eval("623+-382/+*") = 7
 */
