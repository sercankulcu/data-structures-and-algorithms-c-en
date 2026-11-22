/* The division method h(k) = k mod m and the multiplication method (Knuth,
 * s = A * 2^32). With m = 10 the multiples of 10 all fall into bucket 0; the
 * prime m = 11 spreads them out.
 * Examples from the notes: the eight keys of Table 14.3 with m = 10 and
 * m = 11; the CLRS example k = 123456, p = 14 -> 67; also k = 1..5, p = 4.
 * Slides: "Division method", "Multiplication method". */
#include <stdio.h>
#include <stdint.h>

unsigned h_div(unsigned k, unsigned m) { return k % m; }

/* w = 32 bits, m = 2^p; s = A * 2^32 */
uint32_t h_mul(uint32_t k, int p) {
  const uint32_t s = 2654435769u;
  return (uint32_t)(k * s) >> (32 - p);
}

int main(void)
{
    unsigned k[] = {10, 20, 30, 40, 50, 60, 17, 27};
    printf("k       :");
    for (int i = 0; i < 8; i++) printf(" %2u", k[i]);
    printf("\nk mod 10:");
    for (int i = 0; i < 8; i++) printf(" %2u", h_div(k[i], 10));
    printf("\nk mod 11:");
    for (int i = 0; i < 8; i++) printf(" %2u", h_div(k[i], 11));
    printf("\n");

    printf("h_mul(123456, 14) = %u\n", (unsigned) h_mul(123456u, 14));
    printf("h_mul(1..5, 4):");
    for (uint32_t x = 1; x <= 5; x++)
        printf(" %u", (unsigned) h_mul(x, 4));
    printf("\n");
    return 0;
}

/* Expected output:
 * k       : 10 20 30 40 50 60 17 27
 * k mod 10:  0  0  0  0  0  0  7  7
 * k mod 11: 10  9  8  7  6  5  6  5
 * h_mul(123456, 14) = 67
 * h_mul(1..5, 4): 9 3 13 7 1
 */
