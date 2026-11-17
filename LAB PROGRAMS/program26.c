
#include <stdio.h>

int main()
{
    // Original RSA parameters
    long long p = 59;
    long long q = 61;

    long long old_e = 31;
    long long old_d = 3031;

    long long old_n = p * q;

    // New exponents (illustrative values)
    long long new_e = 7;
    long long new_d = 2983;

    // Keeping the same modulus
    long long new_n = old_n;

    printf("RSA PRIVATE KEY LEAKAGE DEMONSTRATION\n");

    printf("\nOriginal RSA Key:\n");
    printf("Public Key  = (%lld, %lld)\n", old_e, old_n);
    printf("Private Key = (%lld, %lld)\n", old_d, old_n);

    printf("\nNew RSA Key:\n");
    printf("Public Exponent  = %lld\n", new_e);
    printf("Private Exponent = %lld\n", new_d);
    printf("New Modulus      = %lld\n", new_n);

    printf("\nChecking Modulus:\n");

    if (old_n == new_n)
    {
        printf("Old and new moduli are identical.\n");
        printf("The original prime factors are still the same.\n");
        printf("Changing exponents alone is NOT sufficient.\n");
    }
    else
    {
        printf("The modulus has changed.\n");
    }

    printf("\nConclusion:\n");
    printf("Generate a completely new RSA key pair.\n");

    return 0;
}
