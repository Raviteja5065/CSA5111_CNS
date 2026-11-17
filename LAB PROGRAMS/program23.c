
#include <stdio.h>

// Permutation function
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

// Generate S-DES keys
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

// S-box function
int sbox(int input, int box[4][4])
{
    int row = ((input & 8) >> 2) | (input & 1);
    int col = (input >> 1) & 3;

    return box[row][col];
}

// S-DES round function
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

// Swap halves
int swap(int input)
{
    return ((input & 15) << 4) | ((input >> 4) & 15);
}

// S-DES encryption
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

// CTR mode encryption and decryption
int main()
{
    int key = 0b0111111101;

    int plaintext[3] = {
        0b00000001,
        0b00000010,
        0b00000100
    };

    int ciphertext[3];
    int decrypted[3];

    int counter = 0;

    printf("CTR MODE ENCRYPTION\n");

    for (int i = 0; i < 3; i++)
    {
        int encryptedCounter = encrypt(counter, key);

        ciphertext[i] = plaintext[i] ^ encryptedCounter;

        printf("\nBlock %d\n", i + 1);
        printf("Counter          : %08d\n",
            (counter / 128) * 10000000 +
            ((counter / 64) % 2) * 1000000 +
            ((counter / 32) % 2) * 100000 +
            ((counter / 16) % 2) * 10000 +
            ((counter / 8) % 2) * 1000 +
            ((counter / 4) % 2) * 100 +
            ((counter / 2) % 2) * 10 +
            (counter % 2));

        printf("Encrypted counter: %02X\n", encryptedCounter);
        printf("Plaintext        : %02X\n", plaintext[i]);
        printf("Ciphertext       : %02X\n", ciphertext[i]);

        counter++;
    }

    printf("\nCTR MODE DECRYPTION\n");

    counter = 0;

    for (int i = 0; i < 3; i++)
    {
        int encryptedCounter = encrypt(counter, key);

        decrypted[i] = ciphertext[i] ^ encryptedCounter;

        printf("Block %d decrypted: %02X\n",
            i + 1, decrypted[i]);

        counter++;
    }

    printf("\nFINAL CIPHERTEXT: ");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 7; j >= 0; j--)
            printf("%d", (ciphertext[i] >> j) & 1);

        printf(" ");
    }

    printf("\nDECRYPTED PLAINTEXT: ");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 7; j >= 0; j--)
            printf("%d", (decrypted[i] >> j) & 1);

        printf(" ");
    }

    printf("\n");

    return 0;
}
