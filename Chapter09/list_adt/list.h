/* List ADT interface: the opaque List type and the operations with their
 * contracts written out.
 * Slide: "The List ADT: What It Does, with the How Hidden". */
#ifndef LIST_H    /* not on the slides: include guard */
#define LIST_H

#include <stdbool.h>  /* not on the slides: bool */

typedef struct list List;             // opaque type

List  *list_create(void);
void   list_destroy(List *L);
int    list_length(const List *L);
bool   list_get(const List *L, int i, int *x);
bool   list_insert(List *L, int i, int x);  // 0<=i<=n
bool   list_delete(List *L, int i, int *x); // 0<=i<n
int    list_find(const List *L, int x);     // -1 if absent

#endif
