#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char plaintext[100];
    char key[100];
    char ciphertext[100];

    int i, j = 0;
    int keyLength;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    scanf("%s", key);

    keyLength = strlen(key);

    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char p = toupper(plaintext[i]);
            char k = toupper(key[j % keyLength]);

            ciphertext[i] =
                ((p - 'A') + (k - 'A')) % 26 + 'A';

            j++;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}