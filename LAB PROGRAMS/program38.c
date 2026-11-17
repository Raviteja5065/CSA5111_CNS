
#include <stdio.h>

// Find GCD
int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }

    return a;
}

// Find modular inverse modulo 26
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

// Convert number into range 0 to 25
int mod26(int x)
{
    return (x % 26 + 26) % 26;
}

int main()
{
    int P[2][2], C[2][2], K[2][2];
    int det, inverse;
    int i, j;

    printf("HILL CIPHER KNOWN-PLAINTEXT ATTACK\n");

    printf("\nEnter plaintext matrix (2x2):\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            scanf("%d", &P[i][j]);
            P[i][j] = mod26(P[i][j]);
        }
    }

    printf("\nEnter corresponding ciphertext matrix (2x2):\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            scanf("%d", &C[i][j]);
            C[i][j] = mod26(C[i][j]);
        }
    }

    // Calculate determinant of plaintext matrix
    det = mod26(P[0][0] * P[1][1] -
                P[0][1] * P[1][0]);

    // Check whether inverse exists
    if (gcd(det, 26) != 1)
    {
        printf("\nPlaintext matrix has no inverse modulo 26.\n");
        printf("Cannot recover the key using these blocks.\n");
        return 1;
    }

    inverse = modInverse(det);

    // Calculate inverse of plaintext matrix
    int Pinv[2][2];

    Pinv[0][0] = mod26(P[1][1] * inverse);
    Pinv[0][1] = mod26(-P[0][1] * inverse);
    Pinv[1][0] = mod26(-P[1][0] * inverse);
    Pinv[1][1] = mod26(P[0][0] * inverse);

    // Calculate K = C * inverse(P) mod 26
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            K[i][j] = 0;

            for (int k = 0; k < 2; k++)
            {
                K[i][j] += C[i][k] * Pinv[k][j];
            }

            K[i][j] = mod26(K[i][j]);
        }
    }

    // Display recovered key
    printf("\nRecovered Hill Cipher Key Matrix:\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%d\t", K[i][j]);
        }

        printf("\n");
    }

    return 0;
}
