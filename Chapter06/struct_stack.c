/* A stack with a struct instead of a global array: the array and the top index
 * live together in a Stack structure; overflow and underflow do not end the
 * program, they return false. An application: reversing a string with a stack.
 * Examples from the notes: 5, 8, 2, 9 are pushed and four pops are done (in the
 * notes CAP = 3, so 9 is rejected; here CAP = 100, so overflow is shown
 * separately by filling the stack); reverse("STACK") = "KCATS".
 * Slides: "Better Design: The Stack as an Object", "Code Trace: Array-Based
 * Stack", "Code Trace: Reversing a String with a Stack". */
#include <stdio.h>
#include <stdbool.h>
#define CAP 100

typedef struct {
    int data[CAP];
    int top;               /* -1 when empty */
} Stack;

void stack_init(Stack *s) { s->top = -1; }
bool stack_empty(const Stack *s)  { return s->top < 0; }
bool stack_full(const Stack *s) { return s->top == CAP - 1; }
int  stack_size(const Stack *s) { return s->top + 1; }
bool stack_top(const Stack *s, int *x) {
    if (stack_empty(s)) return false;
    *x = s->data[s->top];  return true;
}

bool push(Stack *s, int x) {
  if (s->top == CAP - 1) return false; /* overflow */
  s->data[++s->top] = x;
  return true;
}
bool pop(Stack *s, int *x) {
  if (s->top < 0) return false;   /* underflow */
  *x = s->data[s->top--];
  return true;
}

void reverse(char *s) {
  Stack st;  int c, i;
  stack_init(&st);
  for (i = 0; s[i] != '\0'; i++)
    push(&st, s[i]);     /* assume CAP suffices */
  for (i = 0; pop(&st, &c); i++)
    s[i] = (char)c;
}

int main(void)
{
    Stack st;
    int x, i, input[] = {5, 8, 2, 9};
    char s[] = "STACK";

    stack_init(&st);
    for (i = 0; i < 4; i++) {
        bool ok = push(&st, input[i]);
        printf("push %d: %s, size %d\n", input[i], ok ? "true" : "false",
               stack_size(&st));
    }
    if (stack_top(&st, &x)) printf("top = %d\n", x);
    for (i = 0; i < 5; i++) {
        if (pop(&st, &x)) printf("pop: true, x = %d\n", x);
        else printf("pop: false (underflow)\n");
    }
    printf("empty: %s\n", stack_empty(&st) ? "yes" : "no");

    for (i = 0; push(&st, i); i++)       /* push until full */
        ;
    printf("%d pushes succeeded, full: %s, size %d\n", i,
           stack_full(&st) ? "yes" : "no", stack_size(&st));

    reverse(s);
    printf("reverse(\"STACK\") = \"%s\"\n", s);
    return 0;
}

/* Expected output:
 * push 5: true, size 1
 * push 8: true, size 2
 * push 2: true, size 3
 * push 9: true, size 4
 * top = 9
 * pop: true, x = 9
 * pop: true, x = 2
 * pop: true, x = 8
 * pop: true, x = 5
 * pop: false (underflow)
 * empty: yes
 * 100 pushes succeeded, full: yes, size 100
 * reverse("STACK") = "KCATS"
 */
