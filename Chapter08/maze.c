/* Backtracking with a stack in a maze: the path function searches the 8x8
 * maze for a way from the entrance (1,1) to the exit (6,6) and prints the
 * path it finds. The second version (path_short) is a shortened writing of
 * the same loop (names nr/nc, compound literal); both versions find the
 * same path.
 * Slides: "Definitions for the Maze", "The path Routine",
 * "Code Trace: Backtracking with a Stack". */
#include <stdio.h>
#include <stdlib.h>   /* not on the slides: exit, EXIT_FAILURE */

#define FALSE 0       /* not on the slides */
#define TRUE 1        /* not on the slides */

#define MAX_STACK_SIZE 100
#define EXIT_ROW 6
#define EXIT_COL 6
typedef struct { short int vert, horiz; } offsets;
offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                   {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
typedef struct { short int row, col, dir; } element;
element stack[MAX_STACK_SIZE];
int top = -1;
short int mark[8][8];
short int maze[8][8] = {{1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1}, {1,0,1,0,1,1,1,1},
    {1,1,0,1,1,1,1,1}, {1,0,1,1,0,1,1,1},
    {1,1,0,0,1,0,1,1}, {1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1}};

/* not on the slides: stack operations (top is passed by address) */
void push(int *top, element item)
{
    if (*top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full\n");
        exit(EXIT_FAILURE);
    }
    stack[++*top] = item;
}

element pop(int *top)
{
    if (*top == -1) {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack[(*top)--];
}

void path(void) {
  short int row, col, next_row, next_col;
  int i, dir, found = FALSE;
  element position;
  stack[0].row = stack[0].col = 1;
  stack[0].dir = 1;     /* push the start */
  mark[1][1] = 1;  top = 0;
  row = col = 0;  /* not on the slides: against the "may be used uninitialized" warning */
  while (top > -1 && !found) {
    position = pop(&top);     /* next one */
    row = position.row;
    col = position.col;
    dir = position.dir;       /* which way */
    while (dir < 8 && !found) {
      next_row = row + move[dir].vert;
      next_col = col + move[dir].horiz;
      if (next_row == EXIT_ROW &&
          next_col == EXIT_COL)
        found = TRUE;         /* the exit? */
      else if (!maze[next_row][next_col] &&
               !mark[next_row][next_col]) {
        mark[next_row][next_col] = 1;
        position.row = row;   /* came from */
        position.col = col;
        position.dir = ++dir; /* resume dir */
        push(&top, position);
        row = next_row;  col = next_col;
        dir = 0;
      } else ++dir;           /* try another */
    }                         /* back up */
  }
  /* not on the slides: the last part that prints the path (as in the lecture notes) */
  if (found) {
    printf("row col\n");
    for (i = 0; i <= top; i++)        /* the path on the stack */
      printf("%2d%5d\n", stack[i].row, stack[i].col);
    printf("%2d%5d\n", row, col);      /* last position */
    printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
  } else printf("No path to the exit found!\n");
}

/* not on the slides: the loop on the "Maze Step by Step" slide is the body
 * of this function; declarations, setup and printing are the same as in path. */
void path_short(void) {
  short int row = 0, col = 0, nr, nc;
  int i, j, dir, found = FALSE;
  element position;
  for (i = 0; i < 8; i++)             /* clear mark */
    for (j = 0; j < 8; j++)
      mark[i][j] = 0;
  stack[0].row = stack[0].col = 1;
  stack[0].dir = 1;
  mark[1][1] = 1;  top = 0;
  /* slide code: */
while (top > -1 && !found) {
  position = pop(&top);
  row = position.row;  col = position.col;
  dir = position.dir;
  while (dir < 8 && !found) {
    nr = row + move[dir].vert;
    nc = col + move[dir].horiz;
    if (nr == EXIT_ROW && nc == EXIT_COL)
      found = TRUE;
    else if (!maze[nr][nc] &&
             !mark[nr][nc]) {
      mark[nr][nc] = 1;
      position = (element){row, col, ++dir};
      push(&top, position);
      row = nr;  col = nc;  dir = 0;
    } else ++dir;
} }
  /* end of slide code */
  if (found) {
    printf("row col\n");
    for (i = 0; i <= top; i++)
      printf("%2d%5d\n", stack[i].row, stack[i].col);
    printf("%2d%5d\n", row, col);
    printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
  } else printf("No path to the exit found!\n");
}

int main(void)
{
    printf("path:\n");
    path();
    printf("path_short:\n");
    path_short();
    return 0;
}

/* Expected output:
 * path:
 * row col
 *  1    1
 *  2    1
 *  3    2
 *  4    1
 *  5    2
 *  5    3
 *  4    4
 *  5    5
 *  6    6
 * path_short:
 * row col
 *  1    1
 *  2    1
 *  3    2
 *  4    1
 *  5    2
 *  5    3
 *  4    4
 *  5    5
 *  6    6
 */
