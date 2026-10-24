#include <stdio.h>
#include <string.h>

int main() {
    char key[57], C[29], D[29];
    int i;

    printf("Enter a 56-bit binary key: ");
    scanf("%56s", key);

    if (strlen(key) != 56) {
        printf("Invalid key length.\n");
        return 1;
    }

    for (i = 0; i < 56; i++) {
        if (key[i] != '0' && key[i] != '1') {
            printf("Key must contain only 0 and 1.\n");
            return 1;
        }
    }

    for (i = 0; i < 28; i++) {
        C[i] = key[i];
        D[i] = key[i + 28];
    }

    C[28] = '\0';
    D[28] = '\0';

    printf("Left half C: %s\n", C);
    printf("Right half D: %s\n", D);

    printf("First 24 bits of C: ");
    for (i = 0; i < 24; i++)
        putchar(C[i]);

    printf("\nFirst 24 bits of D: ");
    for (i = 0; i < 24; i++)
        putchar(D[i]);

    printf("\nCombined 48-bit demonstration subkey: ");

    for (i = 0; i < 24; i++)
        putchar(C[i]);

    for (i = 0; i < 24; i++)
        putchar(D[i]);

    printf("\n");
    return 0;
}