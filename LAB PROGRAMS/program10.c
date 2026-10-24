#include <stdio.h>
#include <ctype.h>

char m[5][5] = {
    {'M','F','H','I','K'},
    {'U','N','O','P','Q'},
    {'Z','V','W','X','Y'},
    {'E','L','A','R','G'},
    {'D','S','T','B','C'}
};

void find(char c, int *r, int *col) {
    int i, j;

    if (c == 'J') c = 'I';

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if (m[i][j] == c) {
                *r = i;
                *col = j;
                return;
            }
}

int main() {
    char text[500], p[500];
    int i, j = 0, r1, c1, r2, c2;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i]; i++) {
        if (isalpha((unsigned char)text[i])) {
            char c = toupper((unsigned char)text[i]);
            if (c == 'J') c = 'I';
            p[j++] = c;
        }
    }

    if (j % 2 != 0) p[j++] = 'X';
    p[j] = '\0';

    printf("Ciphertext: ");

    for (i = 0; i < j; i += 2) {
        find(p[i], &r1, &c1);
        find(p[i+1], &r2, &c2);

        if (r1 == r2) {
            putchar(m[r1][(c1+1)%5]);
            putchar(m[r2][(c2+1)%5]);
        } else if (c1 == c2) {
            putchar(m[(r1+1)%5][c1]);
            putchar(m[(r2+1)%5][c2]);
        } else {
            putchar(m[r1][c2]);
            putchar(m[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}