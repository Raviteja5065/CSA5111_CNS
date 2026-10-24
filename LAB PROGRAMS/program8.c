#include <stdio.h>
#include <ctype.h>

int main() {
    char plain[500];
    char key[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    int i, x;

    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);

    printf("Ciphertext: ");

    for (i = 0; plain[i] != '\0'; i++) {
        if (isalpha((unsigned char)plain[i])) {
            x = toupper((unsigned char)plain[i]) - 'A';
            putchar(key[x]);
        } else {
            putchar(plain[i]);
        }
    }

    printf("\n");
    return 0;
}