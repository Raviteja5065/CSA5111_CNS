#include <stdio.h>

int main() {
    int a, b, c, d;
    int p1 = 7, p2 = 4, p3 = 11, p4 = 15;
    int x1 = 7, x2 = 8, x3 = 0, x4 = 19;

    printf("Known plaintext: HELP\n");
    printf("Known ciphertext: HIAT\n");

    for (a = 0; a < 26; a++)
    for (b = 0; b < 26; b++)
    for (c = 0; c < 26; c++)
    for (d = 0; d < 26; d++) {
        if ((a*p1 + b*p2) % 26 == x1 &&
            (c*p1 + d*p2) % 26 == x2 &&
            (a*p3 + b*p4) % 26 == x3 &&
            (c*p3 + d*p4) % 26 == x4) {

            printf("Recovered key matrix:\n");
            printf("%d %d\n%d %d\n", a, b, c, d);
            return 0;
        }
    }

    printf("No matching key found.\n");
    return 0;
}