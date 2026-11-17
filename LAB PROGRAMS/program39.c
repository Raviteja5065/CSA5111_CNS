
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char ciphertext[1000];
    char decrypted[1000];

    int frequency[26] = {0};
    int i, key;

    printf("ADDITIVE CIPHER FREQUENCY ATTACK\n");

    printf("\nEnter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Count ciphertext letter frequencies
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)ciphertext[i]))
        {
            char ch = toupper((unsigned char)ciphertext[i]);
            frequency[ch - 'A']++;
        }
    }

    // Display frequency table
    printf("\nCiphertext Letter Frequencies:\n");
    printf("-------------------------------\n");

    for (i = 0; i < 26; i++)
    {
        if (frequency[i] > 0)
        {
            printf("%c : %d\n", 'A' + i, frequency[i]);
        }
    }

    // Try all 26 possible keys
    printf("\nPossible Decrypted Messages:\n");
    printf("-----------------------------\n");

    for (key = 0; key < 26; key++)
    {
        for (i = 0; ciphertext[i] != '\0'; i++)
        {
            if (isalpha((unsigned char)ciphertext[i]))
            {
                char ch = toupper((unsigned char)ciphertext[i]);

                int C = ch - 'A';
                int P = (C - key + 26) % 26;

                decrypted[i] = P + 'A';
            }
            else
            {
                decrypted[i] = ciphertext[i];
            }
        }

        decrypted[i] = '\0';

        printf("Key %2d: %s\n", key, decrypted);
    }

    return 0;
}
