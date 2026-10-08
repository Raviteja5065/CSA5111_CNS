#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char plaintext[100];
    char key[27];
    char ciphertext[100];
    int i, index;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the 26-letter substitution key: ");
    scanf("%26s", key);

    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isupper(plaintext[i]))
        {
            index = plaintext[i] - 'A';
            ciphertext[i] = toupper(key[index]);
        }
        else if (islower(plaintext[i]))
        {
            index = plaintext[i] - 'a';
            ciphertext[i] = tolower(key[index]);
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