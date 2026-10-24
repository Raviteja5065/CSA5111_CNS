#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cipher[1000];
    char english[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    int freq[26] = {0}, used[26] = {0};
    char map[26];
    int i, j, max, index;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    for (i = 0; cipher[i]; i++)
        if (isalpha((unsigned char)cipher[i]))
            freq[toupper((unsigned char)cipher[i]) - 'A']++;

    for (j = 0; j < 26; j++) {
        max = -1;
        index = -1;

        for (i = 0; i < 26; i++)
            if (!used[i] && freq[i] > max) {
                max = freq[i];
                index = i;
            }

        if (index >= 0) {
            used[index] = 1;
            map[index] = english[j];
        }
    }

    printf("Estimated plaintext: ");

    for (i = 0; cipher[i]; i++) {
        if (isalpha((unsigned char)cipher[i]))
            putchar(map[toupper((unsigned char)cipher[i]) - 'A']);
        else
            putchar(cipher[i]);
    }

    printf("\n");
    return 0;
}