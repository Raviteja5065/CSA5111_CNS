
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Find GCD
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// Find modular multiplicative inverse
int modInverse(int a)
{
    int i;

    for (i = 1; i < 26; i++)
    {
        if ((a * i) % 26 == 1)
            return i;
    }

    return -1;
}

int main()
{
    char plaintext[100];
    char ciphertext[100];
    char decrypted[100];

    int a, b, i, inverse;

    printf("AFFINE CAESAR CIPHER\n");

    printf("\nEnter plaintext (uppercase): ");
    scanf("%99s", plaintext);

    printf("Enter key a: ");
    scanf("%d", &a);

    printf("Enter key b: ");
    scanf("%d", &b);

    // Normalize b to the range 0-25
    b = ((b % 26) + 26) % 26;

    // Validate key a
    if (a < 1 || a > 25 || gcd(a, 26) != 1)
    {
        printf("\nInvalid key a!\n");
        printf("Key a must be relatively prime to 26.\n");
        return 1;
    }

    inverse = modInverse(a);

    // Encryption
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (!isupper((unsigned char)plaintext[i]))
        {
            printf("Error: Use uppercase letters A-Z only.\n");
            return 1;
        }

        int x = plaintext[i] - 'A';

        int y = (a * x + b) % 26;

        ciphertext[i] = y + 'A';
    }

    ciphertext[i] = '\0';

    // Decryption
    for (i = 0; ciphertext[i] != '\0'; i++)
    {
        int y = ciphertext[i] - 'A';

        int x = (inverse * (y - b + 26)) % 26;

        decrypted[i] = x + 'A';
    }

    decrypted[i] = '\0';

    printf("\nEncryption Result\n");
    printf("Plaintext  : %s\n", plaintext);
    printf("Ciphertext : %s\n", ciphertext);

    printf("\nDecryption Result\n");
    printf("Ciphertext : %s\n", ciphertext);
    printf("Decrypted  : %s\n", decrypted);

    printf("\nModular Inverse of a: %d\n", inverse);

    return 0;
}
