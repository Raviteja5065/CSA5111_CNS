
#include <stdio.h>

// Extended Euclidean Algorithm
long long extendedGCD(long long a, long long b,
                      long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;

    long long gcd = extendedGCD(b, a % b, &x1, &y1);

    *x = y1;
    *y = x1 - (a / b) * y1;

    return gcd;
}

// Find modular inverse
long long modInverse(long long e, long long phi)
{
    long long x, y;

    long long gcd = extendedGCD(e, phi, &x, &y);

    if (gcd != 1)
        return -1;

    return (x % phi + phi) % phi;
}

int main()
{
    long long n = 3599;
    long long e = 31;

    long long p = 0, q = 0;

    // Find prime factors p and q
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            p = i;
            q = n / i;
            break;
        }
    }

    if (p == 0)
    {
        printf("Factors not found!\n");
        return 1;
    }

    // Calculate Euler's Totient
    long long phi = (p - 1) * (q - 1);

    // Calculate private key
    long long d = modInverse(e, phi);

    printf("\nRSA PRIVATE KEY GENERATION\n");

    printf("\nPublic Key:\n");
    printf("e = %lld\n", e);
    printf("n = %lld\n", n);

    printf("\nPrime Factors:\n");
    printf("p = %lld\n", p);
    printf("q = %lld\n", q);

    printf("\nEuler Totient:\n");
    printf("phi(n) = %lld\n", phi);

    printf("\nPrivate Key:\n");
    printf("d = %lld\n", d);

    printf("\nPrivate Key = (%lld, %lld)\n", d, n);

    return 0;
}
