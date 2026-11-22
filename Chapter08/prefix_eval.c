/* Evaluating a prefix expression: the expression is read from right to
 * left; when an operator comes, the first value popped is the left operand.
 * Slide: "Code Trace: Prefix Evaluation (-+*23*549)". */
#include <stdio.h>
#include <string.h>   /* not on the slides: strlen */
#include <ctype.h>    /* not on the slides: isdigit */

#define MAX 100       /* not on the slides */

/* not on the slides: apply (as in the lecture notes) */
float apply(char op, float op1, float op2) {
  switch (op) {
    case '+': return op1 + op2;
    case '-': return op1 - op2;
    case '*': return op1 * op2;
    case '/': return op1 / op2;
    default:  return 0;
  }
}

float prefix_eval(const char *e) {
  float y[MAX], op1, op2;  int top = -1;
  for (int i = strlen(e) - 1; i >= 0; i--) {
    if (isdigit(e[i])) y[++top] = e[i] - '0';
    else {
      op1 = y[top--];  op2 = y[top--];
      y[++top] = apply(e[i], op1, op2);
    }
  }
  return y[top];
}

int main(void)
{
    const char *expressions[] = { "-+*23*549", "-62", "*-623" };
    int i;

    for (i = 0; i < 3; i++)
        printf("prefix_eval(\"%s\") = %g\n", expressions[i],
               prefix_eval(expressions[i]));
    return 0;
}

/* Expected output:
 * prefix_eval("-+*23*549") = 17
 * prefix_eval("-62") = 4
 * prefix_eval("*-623") = 12
 */
