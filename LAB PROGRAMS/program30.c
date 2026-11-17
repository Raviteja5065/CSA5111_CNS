
#include <stdio.h>

// Toy 8-bit block transformation.
// This is NOT a secure encryption algorithm.
unsigned char encryptBlock(unsigned char input)
{
    return (unsigned char)((5 * input + 7) % 256);
}

// Calculate CBC-MAC for two blocks
unsigned char cbcMac(unsigned char block1,
                     unsigned char block2)
{
    unsigned char c0 = 0;
    unsigned char c1, c2;

    // First block
    c1 = encryptBlock(block1 ^ c0);

    // Second block
    c2 = encryptBlock(block2 ^ c1);

    return c2;
}

int main()
{
    unsigned char X;
    unsigned char T;
    unsigned char extendedBlock;
    unsigned char originalMac;
    unsigned char extendedMac;

    printf("CBC-MAC MESSAGE EXTENSION\n");

    printf("\nEnter one-byte message X (0-255): ");
    scanf("%hhu", &X);

    // MAC of the original one-block message
    T = encryptBlock(X);

    // Construct second block: X XOR T
    extendedBlock = X ^ T;

    // MAC of original message
    originalMac = encryptBlock(X);

    // MAC of extended two-block message
    extendedMac = cbcMac(X, extendedBlock);

    printf("\nOriginal Message:\n");
    printf("X = %u\n", X);
    printf("MAC T = %u\n", originalMac);

    printf("\nExtended Message:\n");
    printf("First Block  = %u\n", X);
    printf("Second Block = X XOR T = %u\n", extendedBlock);

    printf("\nMAC Comparison:\n");
    printf("Original MAC = %u\n", originalMac);
    printf("Extended MAC = %u\n", extendedMac);

    if (originalMac == extendedMac)
    {
        printf("\nSUCCESS: Both MAC values are equal.\n");
    }
    else
    {
        printf("\nMAC values are different.\n");
    }

    return 0;
}
