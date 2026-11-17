
#include <stdio.h>
#include <string.h>

#define N 3233
#define E 17
#define D 2753

// Modular exponentiation
long long powerMod(long long base, long long exp, long long mod)
{
    long long result = 1;

    base = base % mod;

    while (exp > 0)
    {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }

    return result;
}

int main()
{
    char plaintext[100];
    long long ciphertext[100];
    int length, i;

    printf("Enter uppercase plaintext: ");
    scanf("%99s", plaintext);

    length = strlen(plaintext);

    printf("\nTEXTBOOK RSA ENCRYPTION\n");

    printf("\nCharacter  Number  Ciphertext\n");

    for (i = 0; i < length; i++)
    {
        if (plaintext[i] < 'A' || plaintext[i] > 'Z')
        {
            printf("Only uppercase A-Z characters are allowed.\n");
            return 1;
        }

        // Convert character to number
        int m = plaintext[i] - 'A';

        // RSA encryption
        ciphertext[i] = powerMod(m, E, N);

        printf("    %c        %2d       %lld\n",
               plaintext[i], m, ciphertext[i]);
    }

    printf("\nRSA DECRYPTION\n");

    printf("Decrypted plaintext: ");

    for (i = 0; i < length; i++)
    {
        // RSA decryption
        long long m = powerMod(ciphertext[i], D, N);

        printf("%c", (char)('A' + m));
    }

    printf("\n");

    printf("\nSecurity observation:\n");
    printf("Repeated characters produce identical ciphertext.\n");

    return 0;
}
