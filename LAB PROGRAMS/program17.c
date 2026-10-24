#include <stdio.h>

int main() {
    int K[16], i;

    for (i = 0; i < 16; i++)
        K[i] = i + 1;

    printf("DES decryption subkey order:\n");

    for (i = 15; i >= 0; i--)
        printf("K%d ", K[i]);

    printf("\n");
    return 0;
}