
#include <stdio.h>

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
    long long p, g;
    long long a, b;
    long long A, B;
    long long keyAlice, keyBob;

    printf("DIFFIE-HELLMAN KEY EXCHANGE\n");

    // Public values
    printf("\nEnter prime number p: ");
    scanf("%lld", &p);

    printf("Enter generator g: ");
    scanf("%lld", &g);

    // Private values
    printf("Enter Alice's private key a: ");
    scanf("%lld", &a);

    printf("Enter Bob's private key b: ");
    scanf("%lld", &b);

    // Calculate public keys
    A = powerMod(g, a, p);
    B = powerMod(g, b, p);

    printf("\nAlice's public key = %lld\n", A);
    printf("Bob's public key   = %lld\n", B);

    // Calculate shared secret
    keyAlice = powerMod(B, a, p);
    keyBob = powerMod(A, b, p);

    printf("\nAlice's shared key = %lld\n", keyAlice);
    printf("Bob's shared key   = %lld\n", keyBob);

    // Verify shared keys
    if (keyAlice == keyBob)
    {
        printf("\nSUCCESS: Both keys are equal.\n");
        printf("Shared secret key = %lld\n", keyAlice);
    }
    else
    {
        printf("\nERROR: Shared keys are not equal.\n");
    }

    return 0;
}
