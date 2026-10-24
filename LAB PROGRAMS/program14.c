#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char p[] = "SENDMOREMONEY";
    char target[] = "CASHNOTNEEDED";
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    int i, c, t;

    printf("Ciphertext: ");

    for (i = 0; p[i]; i++) {
        c = ((p[i] - 'A') + key[i]) % 26;
        putchar(c + 'A');
    }

    printf("\nKey for target plaintext: ");

    for (i = 0; p[i]; i++) {
        c = ((p[i] - 'A') + key[i]) % 26;
        t = target[i] - 'A';
        printf("%d ", (c - t + 26) % 26);
    }

    printf("\n");
    return 0;
}