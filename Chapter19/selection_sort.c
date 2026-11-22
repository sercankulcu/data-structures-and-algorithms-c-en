/* Selection sort (selection): in every pass the smallest item of a[i..R] is
 * found and swapped with a[i]. The example is the array [29, 10, 14, 37, 13]
 * from the trace in the notes.
 * Slides: "Selection Sort", "Code Trace: selection()". */
#include <stdio.h>   /* not on the slides */

/* not on the slides: macros from the "Common Setup" slide */
#define less(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void selection(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int min = i;
        for (int j = i + 1; j <= R; j++)
            if (less(a[j], a[min]))
                min = j;
        SWAP(a[i], a[min]);
    }
}

/* not on the slides: prints the array */
static void print_array(const char *name, const int a[], int n) {
    printf("%s", name);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int a[] = {29, 10, 14, 37, 13};
    print_array("before:", a, 5);
    selection(a, 0, 4);
    print_array("after: ", a, 5);
    return 0;
}


/* Expected output:
 * before: 29 10 14 37 13
 * after:  10 13 14 29 37
 */
