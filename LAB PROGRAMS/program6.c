#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char c[500];
    int i, x, p;

    printf("Enter ciphertext: ");
    fgets(c, sizeof(c), stdin);

    printf("Decrypted text: ");

    for (i = 0; c[i] != '\0'; i++) {
        if (isalpha((unsigned char)c[i])) {
            x = toupper((unsigned char)c[i]) - 'A';
            p = (9 * (x - 15 + 26)) % 26;
            putchar(p + 'A');
        } else {
            putchar(c[i]);
        }
    }

    return 0;
}