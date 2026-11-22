/* Evaluating a postfix expression, global version: get_token reads the
 * expression token by token, eval works on the global expr and a global
 * stack.
 * Slides: "Tokens: get_token", "Postfix Evaluation: eval (Global Version)". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: exit */

#define MAX_SIZE 100  /* not on the slides */

typedef enum { lparen, rparen, plus, minus,
    times, divide, mod, eos, operand } precedence;

precedence get_token(const char *expr, char *symbol, int *n) {
    *symbol = expr[(*n)++];
    switch (*symbol) {
        case '(':  return lparen;
        case ')':  return rparen;
        case '+':  return plus;
        case '-':  return minus;
        case '/':  return divide;
        case '*':  return times;
        case '%':  return mod;
        case '\0': return eos;
        default:   return operand;
    }
}

/* global version: external dependencies */
char expr[] = "42/2-33*+42*-";
float stack[MAX_SIZE];
float eval(void);

/* not on the slides: stack operations on the global stack */
void push(int *top, float x)
{
    if (*top >= MAX_SIZE - 1) {
        fprintf(stderr, "Stack is full\n");
        exit(EXIT_FAILURE);
    }
    stack[++*top] = x;
}

float pop(int *top)
{
    if (*top == -1) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack[(*top)--];
}

/* not on the slides: apply (as in the lecture notes) */
float apply(precedence token, float op1, float op2) {
    switch (token) {
        case plus:   return op1 + op2;
        case minus:  return op1 - op2;
        case times:  return op1 * op2;
        case divide: return op1 / op2;
        case mod:    return (int)op1 % (int)op2;
        default:     return 0;   /* not an operator: never reached */
    }
}

float eval(void) {
    char symbol;  precedence token;
    float op1, op2;
    int n = 0, top = -1;
    token = get_token(expr, &symbol, &n);
    while (token != eos) {
        if (token == operand)
            push(&top, symbol - '0');
        else {
            op2 = pop(&top);   /* right operand first */
            op1 = pop(&top);
            push(&top, apply(token, op1, op2));
        }
        token = get_token(expr, &symbol, &n);
    }
    return pop(&top);   /* the one left is the result */
}

int main(void)
{
    const char *test = "(7%3)";
    char symbol;
    int n = 0;
    precedence t;

    /* get_token: the tokens of the expression "(7%3)" */
    printf("get_token(\"%s\"):", test);
    do {
        t = get_token(test, &symbol, &n);
        printf(" %d", (int)t);
    } while (t != eos);
    printf("\n");

    printf("eval() gives %s = %g\n", expr, eval());
    return 0;
}

/* Expected output:
 * get_token("(7%3)"): 0 8 6 8 1 7
 * eval() gives 42/2-33*+42*- = 1
 */
