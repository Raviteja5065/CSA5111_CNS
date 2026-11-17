
#include <stdio.h>

int permute(int input, int *table, int size, int bits)
{
    int output = 0;

    for (int i = 0; i < size; i++)
    {
        output <<= 1;
        output |= (input >> (bits - table[i])) & 1;
    }

    return output;
}

void generateKeys(int key, int *k1, int *k2)
{
    int p10[] = {3,5,2,7,4,10,1,9,8,6};
    int p8[] = {6,3,7,4,8,5,10,9};

    int temp = permute(key, p10, 10, 10);

    int left = (temp >> 5) & 31;
    int right = temp & 31;

    left = ((left << 1) | (left >> 4)) & 31;
    right = ((right << 1) | (right >> 4)) & 31;

    *k1 = permute((left << 5) | right, p8, 8, 10);

    left = ((left << 2) | (left >> 3)) & 31;
    right = ((right << 2) | (right >> 3)) & 31;

    *k2 = permute((left << 5) | right, p8, 8, 10);
}

int sbox(int input, int box[4][4])
{
    int row = ((input & 8) >> 2) | (input & 1);
    int col = (input >> 1) & 3;

    return box[row][col];
}

int fk(int input, int key)
{
    int ep[] = {4,1,2,3,2,3,4,1};
    int p4[] = {2,4,3,1};

    int s0[4][4] = {
        {1,0,3,2},
        {3,2,1,0},
        {0,2,1,3},
        {3,1,3,2}
    };

    int s1[4][4] = {
        {0,1,2,3},
        {2,0,1,3},
        {3,0,1,0},
        {2,1,0,3}
    };

    int right = input & 15;

    int expanded = permute(right, ep, 8, 4);
    expanded ^= key;

    int leftS = sbox((expanded >> 4) & 15, s0);
    int rightS = sbox(expanded & 15, s1);

    int combined = (leftS << 2) | rightS;

    int result = permute(combined, p4, 4, 4);

    return ((((input >> 4) ^ result) & 15) << 4) | right;
}

int swap(int input)
{
    return ((input & 15) << 4) | ((input >> 4) & 15);
}

int encrypt(int input, int key)
{
    int ip[] = {2,6,3,1,4,8,5,7};
    int ip1[] = {4,1,3,5,7,2,8,6};

    int k1, k2;

    generateKeys(key, &k1, &k2);

    int temp = permute(input, ip, 8, 8);

    temp = fk(temp, k1);
    temp = swap(temp);
    temp = fk(temp, k2);

    return permute(temp, ip1, 8, 8);
}

int decrypt(int input, int key)
{
    int ip[] = {2,6,3,1,4,8,5,7};
    int ip1[] = {4,1,3,5,7,2,8,6};

    int k1, k2;

    generateKeys(key, &k1, &k2);

    int temp = permute(input, ip, 8, 8);

    temp = fk(temp, k2);
    temp = swap(temp);
    temp = fk(temp, k1);

    return permute(temp, ip1, 8, 8);
}

int main()
{
    int key = 0b0111111101;
    int iv = 0b10101010;

    int plaintext[2] = {
        0b00000001,
        0b00100011
    };

    int ciphertext[2];
    int decrypted[2];

    int previous = iv;

    printf("CBC ENCRYPTION\n");

    for (int i = 0; i < 2; i++)
    {
        int xorResult = plaintext[i] ^ previous;

        ciphertext[i] = encrypt(xorResult, key);

        printf("\nBlock %d\n", i + 1);
        printf("Plaintext : %02X\n", plaintext[i]);
        printf("Previous  : %02X\n", previous);
        printf("XOR       : %02X\n", xorResult);
        printf("Ciphertext: %02X\n", ciphertext[i]);

        previous = ciphertext[i];
    }

    printf("\nCBC DECRYPTION\n");

    previous = iv;

    for (int i = 0; i < 2; i++)
    {
        int decryptedValue = decrypt(ciphertext[i], key);

        decrypted[i] = decryptedValue ^ previous;

        printf("\nBlock %d\n", i + 1);
        printf("Ciphertext       : %02X\n", ciphertext[i]);
        printf("Decrypted value  : %02X\n", decryptedValue);
        printf("Previous block   : %02X\n", previous);
        printf("Recovered plaintext: %02X\n", decrypted[i]);

        previous = ciphertext[i];
    }

    printf("\nFINAL RESULTS\n");

    printf("Ciphertext: ");
    for (int i = 0; i < 2; i++)
        printf("%08d ", 
            (int)(
                ((ciphertext[i] >> 7) & 1) * 10000000 +
                ((ciphertext[i] >> 6) & 1) * 1000000 +
                ((ciphertext[i] >> 5) & 1) * 100000 +
                ((ciphertext[i] >> 4) & 1) * 10000 +
                ((ciphertext[i] >> 3) & 1) * 1000 +
                ((ciphertext[i] >> 2) & 1) * 100 +
                ((ciphertext[i] >> 1) & 1) * 10 +
                (ciphertext[i] & 1)
            )
        );

    printf("\nDecrypted plaintext: ");

    for (int i = 0; i < 2; i++)
    {
        for (int j = 7; j >= 0; j--)
            printf("%d", (decrypted[i] >> j) & 1);

        printf(" ");
    }

    printf("\n");

    return 0;
}
