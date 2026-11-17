
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

// Modular inverse
long long modInverse(long long a, long long mod)
{
    long long x, y;

    long long gcd = extendedGCD(a, mod, &x, &y);

    if (gcd != 1)
        return -1;

    return (x % mod + mod) % mod;
}

// Normalize a value modulo mod
long long normalize(long long value, long long mod)
{
    return (value % mod + mod) % mod;
}

int main()
{
    long long q = 23;

    // Illustrative DSA values
    long long k = 7;
    long long privateKey = 5;
    long long r = 3;

    long long h1 = 8;
    long long h2 = 12;

    long long invK;
    long long invDifference;

    long long s1, s2;
    long long recoveredK, recoveredPrivateKey;

    // Calculate inverse of k
    invK = modInverse(k, q);

    // Generate two signatures using the same k and r
    s1 = normalize(invK * (h1 + privateKey * r), q);
    s2 = normalize(invK * (h2 + privateKey * r), q);

    printf("DSA NONCE REUSE DEMONSTRATION\n");

    printf("\nOriginal values:\n");
    printf("q = %lld\n", q);
    printf("Private key x = %lld\n", privateKey);
    printf("Nonce k = %lld\n", k);

    printf("\nSignature 1:\n");
    printf("H(m1) = %lld\n", h1);
    printf("r = %lld\n", r);
    printf("s1 = %lld\n", s1);

    printf("\nSignature 2:\n");
    printf("H(m2) = %lld\n", h2);
    printf("r = %lld\n", r);
    printf("s2 = %lld\n", s2);

    // Recover k from the two signatures
    invDifference = modInverse(
        normalize(s1 - s2, q), q);

    if (invDifference == -1)
    {
        printf("\nCannot recover nonce: inverse does not exist.\n");
        return 1;
    }

    recoveredK = normalize(
        (h1 - h2) * invDifference, q);

    // Recover private key
    recoveredPrivateKey = normalize(
        (s1 * recoveredK - h1) *
        modInverse(r, q), q);

    printf("\nRecovered values:\n");
    printf("Recovered k = %lld\n", recoveredK);
    printf("Recovered private key = %lld\n",
           recoveredPrivateKey);

    if (recoveredPrivateKey == privateKey)
        printf("\nPrivate key successfully recovered.\n");

    return 0;
}
