/* Insertion sort (insertion): a[i] is put in place by shifting right-to-left
 * inside the sorted prefix a[L..i-1]. Two examples from the notes: the whole
 * array [7, 2, 9, 5, 1], and only a[2..5] of [9, 8, 7, 1, 6, 5, 0] (thanks to
 * the j >= L bound, a[0], a[1] and a[6] are not touched).
 * Slides: "Insertion Sort: Two Versions", "Code Trace: insertion()". */
#include <stdio.h>   /* not on the slides */

void insertion(int a[], int L, int R) {
    for (int i = L + 1; i <= R; i++) {
        int v = a[i];      // to insert
        int j = i - 1;     // a[L..i-1] sorted
        while (j >= L && a[j] > v) {
            a[j + 1] = a[j]; // shift right
            j--;
        }
        a[j + 1] = v;
    }
}

/* not on the slides: prints the array */
static void print_array(const char *name, const int a[], int n) {
    printf("%s", name);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* not on the slides */
    int a[] = {7, 2, 9, 5, 1};
    insertion(a, 0, 4);
    print_array("insertion(a, 0, 4):", a, 5);

    int b[] = {9, 8, 7, 1, 6, 5, 0};
    insertion(b, 2, 5);
    print_array("insertion(b, 2, 5):", b, 7);
    return 0;
}


/* Expected output:
 * insertion(a, 0, 4): 1 2 5 7 9
 * insertion(b, 2, 5): 9 8 1 5 6 7 0
 */
