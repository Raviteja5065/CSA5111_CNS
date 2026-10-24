#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cipher[500], result[500];
    int shift, i, j, score;
    int bestScore = -1, bestShift = 0;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    for (shift = 0; shift < 26; shift++) {
        score = 0;

        for (i = 0; cipher[i]; i++) {
            if (isalpha((unsigned char)cipher[i])) {
                char ch = toupper((unsigned char)cipher[i]);
                result[i] = (ch - 'A' - shift + 26) % 26 + 'A';
                if (result[i] == 'E') score += 3;
                if (result[i] == 'T') score += 2;
                if (result[i] == 'A' ||
                    result[i] == 'O' ||
                    result[i] == 'I') score++;
            } else {
                result[i] = cipher[i];
            }
        }

        result[i] = '\0';

        if (score > bestScore) {
            bestScore = score;
            bestShift = shift;
        }
    }

    printf("Most likely shift: %d\n", bestShift);
    printf("Possible plaintext: ");

    for (j = 0; cipher[j]; j++) {
        if (isalpha((unsigned char)cipher[j]))
            putchar((toupper((unsigned char)cipher[j])
                     - 'A' - bestShift + 26) % 26 + 'A');
        else
            putchar(cipher[j]);
    }

    return 0;
}