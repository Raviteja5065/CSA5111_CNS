
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plaintext[100];
    char key[100];
    char ciphertext[100];
    char decrypted[100];

    int i, length;

    printf("ONE-TIME PAD USING VIGENERE CIPHER\n");

    printf("\nEnter plaintext (uppercase): ");
    scanf("%99s", plaintext);

    printf("Enter key (uppercase): ");
    scanf("%99s", key);

    length = strlen(plaintext);

    // Check key length
    if (strlen(key) != length)
    {
        printf("\nError: Key length must equal plaintext length.\n");
        return 1;
    }

    // Check that input contains only letters
    for (i = 0; i < length; i++)
    {
        if (!isupper((unsigned char)plaintext[i]) ||
            !isupper((unsigned char)key[i]))
        {
            printf("Error: Use uppercase letters A-Z only.\n");
            return 1;
        }
    }

    // Encryption
    for (i = 0; i < length; i++)
    {
        int P = plaintext[i] - 'A';
        int K = key[i] - 'A';

        int C = (P + K) % 26;

        ciphertext[i] = C + 'A';
    }

    ciphertext[length] = '\0';

    // Decryption
    for (i = 0; i < length; i++)
    {
        int C = ciphertext[i] - 'A';
        int K = key[i] - 'A';

        int P = (C - K + 26) % 26;

        decrypted[i] = P + 'A';
    }

    decrypted[length] = '\0';

    printf("\nEncryption Result\n");
    printf("Plaintext  : %s\n", plaintext);
    printf("Key        : %s\n", key);
    printf("Ciphertext : %s\n", ciphertext);

    printf("\nDecryption Result\n");
    printf("Ciphertext : %s\n", ciphertext);
    printf("Key        : %s\n", key);
    printf("Decrypted  : %s\n", decrypted);

    return 0;
}
