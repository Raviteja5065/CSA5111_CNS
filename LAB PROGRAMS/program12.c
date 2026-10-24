#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[500], p[500], c[500];
    int i, j = 0, a, b, x, y;

    int K[2][2] = {{9, 4}, {5, 7}};
    int D[2][2] = {{5, 12}, {15, 25}};

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i]; i++)
        if (isalpha((unsigned char)text[i]))
            p[j++] = toupper((unsigned char)text[i]);

    if (j % 2) p[j++] = 'X';
    p[j] = '\0';

    for (i = 0; i < j; i += 2) {
        a = p[i] - 'A';
        b = p[i + 1] - 'A';
        c[i] = (K[0][0]*a + K[0][1]*b) % 26 + 'A';
        c[i+1] = (K[1][0]*a + K[1][1]*b) % 26 + 'A';
    }
    c[j] = '\0';

    printf("Ciphertext: %s\n", c);
    printf("Decrypted text: ");

    for (i = 0; i < j; i += 2) {
        a = c[i] - 'A';
        b = c[i+1] - 'A';
        x = (D[0][0]*a + D[0][1]*b) % 26;
        y = (D[1][0]*a + D[1][1]*b) % 26;
        putchar(x + 'A');
        putchar(y + 'A');
    }

    printf("\n");
    return 0;
}