/* Declaring a one-dimensional array, the address formula
 * (alpha + i * sizeof(int)) and sizeof. Slide: "One-Dimensional Arrays
 * in C". The values are for 64-bit Linux (sizeof(int) = 4). */
#include <stdio.h>

int main(void) {  /* not on the slides */
  int list[5], *plist[5];
  /* list : 5 ints         */
  /* plist: 5 int pointers */
  int i;

  for (i = 0; i < 5; i++) {     /* not on the slides: fill the arrays */
    list[i] = 10 * (i + 1);
    plist[i] = &list[i];
  }

  i = 3;
  /* list[i]  -- address: alpha + i * sizeof(int) */
  printf("list[%d] = %d\n", i, list[i]);
  printf("&list[%d] - &list[0] = %td elements = %td bytes\n", i,
         &list[i] - &list[0],
         (char *)&list[i] - (char *)&list[0]);
  /* sizeof list  -- 5 * sizeof(int) bytes */
  printf("sizeof list = %zu, 5 * sizeof(int) = %zu\n",
         sizeof list, 5 * sizeof(int));
  printf("*plist[2] = %d\n", *plist[2]);
  return 0;
}

/* Expected output:
 * list[3] = 40
 * &list[3] - &list[0] = 3 elements = 12 bytes
 * sizeof list = 20, 5 * sizeof(int) = 20
 * *plist[2] = 30
 */
