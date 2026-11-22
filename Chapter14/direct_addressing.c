/* Direct addressing: the key is itself the index of the array; T[k].used
 * says whether the cell is occupied. Because a global array starts out as
 * zeros, the table starts out empty.
 * Example from the notes: Ali, Can, Ece, Naz are written into cells 2, 3,
 * 5, 8; every key from 0 to 9 is looked up.
 * Slide: "Direct addressing". */
#include <stdio.h>
#include <stddef.h>


typedef struct { int used; char name[16]; } rec;
rec T[10];                 /* key = index */

rec *da_search(int k) {
  return T[k].used ? &T[k] : NULL;
}

/* not on the slides: insertion sets T[k].used = 1 and writes the data */
static void da_insert(int k, const char *name) {
    T[k].used = 1;
    snprintf(T[k].name, sizeof T[k].name, "%s", name);
}

int main(void)
{
    da_insert(2, "Ali");
    da_insert(3, "Can");
    da_insert(5, "Ece");
    da_insert(8, "Naz");
    for (int k = 0; k < 10; k++) {
        rec *p = da_search(k);
        printf("da_search(%d) = %s\n", k, p ? p->name : "NULL");
    }
    return 0;
}

/* Expected output:
 * da_search(0) = NULL
 * da_search(1) = NULL
 * da_search(2) = Ali
 * da_search(3) = Can
 * da_search(4) = NULL
 * da_search(5) = Ece
 * da_search(6) = NULL
 * da_search(7) = NULL
 * da_search(8) = Naz
 * da_search(9) = NULL
 */
