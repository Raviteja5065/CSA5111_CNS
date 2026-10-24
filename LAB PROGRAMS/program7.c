#include <stdio.h>
#include <ctype.h>

int main() {
    char c[500];
    char key[27];
    int i, x;

    printf("Enter ciphertext: ");
    fgets(c, sizeof(c), stdin);

    printf("Enter 26-letter decryption key: ");
    scanf("%26s", key);

    printf("Decrypted text: ");

    for (i = 0; c[i] != '\0'; i++) {
        if (isalpha((unsigned char)c[i])) {
            x = toupper((unsigned char)c[i]) - 'A';
            putchar(key[x]);
        } else {
            putchar(c[i]);
        }
    }

    printf("\n");
    return 0;
}