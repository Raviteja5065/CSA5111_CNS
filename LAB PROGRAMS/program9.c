#include <stdio.h>
#include <string.h>
#include <ctype.h>

char m[5][5];

void makeMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;
    char s[26];

    for (i = 0; key[i]; i++) {
        char c = toupper((unsigned char)key[i]);
        if (c == 'J') c = 'I';

        if (c >= 'A' && c <= 'Z' && !used[c-'A']) {
            s[k++] = c;
            used[c-'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++) {
        if (i == ('J' - 'A')) continue;
        if (!used[i]) s[k++] = 'A' + i;
    }

    k = 0;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            m[i][j] = s[k++];
}

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
    char key[100], text[500], a, b;
    int i, r1, c1, r2, c2;

    printf("Enter keyword: ");
    scanf("%99s", key);

    makeMatrix(key);

    printf("Enter even-length ciphertext: ");
    scanf("%499s", text);

    printf("Plaintext: ");

    for (i = 0; text[i] && text[i+1]; i += 2) {
        a = toupper((unsigned char)text[i]);
        b = toupper((unsigned char)text[i+1]);

        find(a, &r1, &c1);
        find(b, &r2, &c2);

        if (r1 == r2) {
            putchar(m[r1][(c1+4)%5]);
            putchar(m[r2][(c2+4)%5]);
        } else if (c1 == c2) {
            putchar(m[(r1+4)%5][c1]);
            putchar(m[(r2+4)%5][c2]);
        } else {
            putchar(m[r1][c2]);
            putchar(m[r2][c1]);
        }
    }

    printf("\n");
    return 0;
}