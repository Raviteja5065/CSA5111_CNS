
#include <stdio.h>

// Function to calculate GCD
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int main()
{
    long long n, m, commonFactor;

    printf("Enter RSA modulus (n): ");
    scanf("%lld", &n);

    printf("Enter plaintext block (m): ");
    scanf("%lld", &m);

    // Calculate GCD of plaintext and modulus
    commonFactor = gcd(m, n);

    printf("\nRSA COMMON FACTOR CHECK\n");

    printf("Modulus n = %lld\n", n);
    printf("Plaintext m = %lld\n", m);
    printf("GCD(m, n) = %lld\n", commonFactor);

    if (commonFactor == 1)
    {
        printf("\nNo common factor greater than 1 found.\n");
        printf("This plaintext does not reveal a factor of n.\n");
    }
    else if (commonFactor == n)
    {
        printf("\nThe plaintext is a multiple of n.\n");
        printf("This does not reveal a non-trivial factor.\n");
    }
    else
    {
        printf("\nA non-trivial common factor is found!\n");
        printf("One factor of n = %lld\n", commonFactor);
        printf("Other factor = %lld\n", n / commonFactor);

        printf("\nThe modulus n has been factored.\n");
    }

    return 0;
}
