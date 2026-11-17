
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char ciphertext[1000];

    int frequency[26] = {0};
    int i, j, temp;

    char letters[26];

    printf("MONOALPHABETIC SUBSTITUTION FREQUENCY ATTACK\n");

    printf("\nEnter ciphertext:\n");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Count frequency of each letter
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)ciphertext[i]))
        {
            char ch = toupper((unsigned char)ciphertext[i]);

            frequency[ch - 'A']++;
        }
    }

    // Initialize alphabet array
    for (i = 0; i < 26; i++)
    {
        letters[i] = 'A' + i;
    }

    // Sort letters by descending frequency
    for (i = 0; i < 25; i++)
    {
        for (j = i + 1; j < 26; j++)
        {
            if (frequency[i] < frequency[j])
            {
                temp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp;

                char tempChar = letters[i];
                letters[i] = letters[j];
                letters[j] = tempChar;
            }
        }
    }

    // Display top 10 letters
    printf("\nTop 10 Most Frequent Ciphertext Letters\n");
    printf("----------------------------------------\n");
    printf("Letter\tFrequency\n");

    for (i = 0; i < 10; i++)
    {
        if (frequency[i] > 0)
        {
            printf("%c\t%d\n", letters[i], frequency[i]);
        }
    }

    // Common English frequency order
    printf("\nPossible English Letter Mapping:\n");

    char english[] = "ETAOINSHRD";

    for (i = 0; i < 10; i++)
    {
        if (frequency[i] > 0)
        {
            printf("%c -> %c\n", letters[i], english[i]);
        }
    }

    return 0;
}
