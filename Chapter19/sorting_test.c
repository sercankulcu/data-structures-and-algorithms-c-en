/* Common setup for testing sorting routines: the less and SWAP macros and a
 * main that sorts N = 15 random numbers (rand() % 50) with selection sort.
 * Since rand() is called without a seed, it produces the same array on every
 * run; the numbers depend on the C library. The expected output below is for
 * glibc (Linux, CI).
 * Slides: "Common Setup: ...", "Selection Sort". */
#include <stdio.h>   /* not on the slides: printf */
#include <stdlib.h>  /* not on the slides: malloc, free, rand */

#define N 15
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* on the slides it is a separate slide: defined before main */
void selection(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int min = i;
        for (int j = i + 1; j <= R; j++)
            if (less(a[j], a[min]))
                min = j;
        SWAP(a[i], a[min]);
    }
}

int main(void) {
    int *a = malloc(N * sizeof *a);
    if (a == NULL) return 1;
    for (int i = 0; i < N; i++)
        a[i] = rand() % 50;
    selection(a, 0, N - 1);   /* call the sorting routine */
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    free(a);
    return 0;
}


/* Expected output (glibc; trailing space at the end of the line, no newline):
 * 9 12 13 15 21 27 27 33 35 36 36 40 42 43 49 
 */
