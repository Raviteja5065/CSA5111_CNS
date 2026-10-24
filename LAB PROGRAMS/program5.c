#include <stdio.h>
#include <ctype.h>

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

int main()
{
    char plaintext[100];
    char ciphertext[100];

    int a, b;
    int i, p, c;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    /* Check whether a is valid */
    if (gcd(a, 26) != 1)
    {
        printf("Invalid value of a.\n");
        printf("a must be relatively prime to 26.\n");

        return 0;
    }

    for (i = 0; plaintext[i] != '\0'; i++)
    {
        if (isupper(plaintext[i]))
        {
            p = plaintext[i] - 'A';
            c = (a * p + b) % 26;
            ciphertext[i] = c + 'A';
        }
        else if (islower(plaintext[i]))
        {
            p = plaintext[i] - 'a';
            c = (a * p + b) % 26;
            ciphertext[i] = c + 'a';
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