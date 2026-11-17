
#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8
#define MAX 1024

// S-DES permutation functions
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

// S-DES key generation
void generateKeys(int key, int *k1, int *k2)
{
    int p10[] = {3,5,2,7,4,10,1,9,8,6};
    int p8[]  = {6,3,7,4,8,5,10,9};

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

    return ((input >> 4) ^ permute(combined, p4, 4, 4)) << 4
           | right;
}

int swap(int input)
{
    return ((input & 15) << 4) | ((input >> 4) & 15);
}

// S-DES encryption
int encryptBlock(int input, int key)
{
    int ip[]  = {2,6,3,1,4,8,5,7};
    int ip1[] = {4,1,3,5,7,2,8,6};

    int k1, k2;
    generateKeys(key, &k1, &k2);

    int temp = permute(input, ip, 8, 8);

    temp = fk(temp, k1);
    temp = swap(temp);
    temp = fk(temp, k2);

    return permute(temp, ip1, 8, 8);
}

// S-DES decryption
int decryptBlock(int input, int key)
{
    int ip[]  = {2,6,3,1,4,8,5,7};
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
    int choice, key, iv;
    int n;
    unsigned char plain[MAX], cipher[MAX], decrypted[MAX];

    printf("1. ECB Mode\n");
    printf("2. CBC Mode\n");
    printf("3. CFB Mode\n");

    printf("Enter mode: ");
    scanf("%d", &choice);

    printf("Enter 10-bit key (0-1023): ");
    scanf("%d", &key);

    printf("Enter number of plaintext bytes: ");
    scanf("%d", &n);

    if (choice < 1 || choice > 3 ||
        key < 0 || key > 1023 ||
        n < 1 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter plaintext bytes (0-255): ");

    for (int i = 0; i < n; i++)
        scanf("%hhu", &plain[i]);

    iv = 0;

    if (choice == 2 || choice == 3)
    {
        printf("Enter 8-bit IV (0-255): ");
        scanf("%d", &iv);

        if (iv < 0 || iv > 255)
        {
            printf("Invalid IV!\n");
            return 1;
        }
    }

    int previous = iv;

    // Encryption
    for (int i = 0; i < n; i++)
    {
        if (choice == 1)
        {
            cipher[i] = encryptBlock(plain[i], key);
        }
        else if (choice == 2)
        {
            cipher[i] = encryptBlock(plain[i] ^ previous, key);
            previous = cipher[i];
        }
        else
        {
            cipher[i] = plain[i] ^ encryptBlock(previous, key);
            previous = cipher[i];
        }
    }

    printf("\nEncrypted ciphertext:\n");

    for (int i = 0; i < n; i++)
        printf("%02X ", cipher[i]);

    // Decryption
    previous = iv;

    for (int i = 0; i < n; i++)
    {
        if (choice == 1)
        {
            decrypted[i] = decryptBlock(cipher[i], key);
        }
        else if (choice == 2)
        {
            decrypted[i] = decryptBlock(cipher[i], key) ^ previous;
            previous = cipher[i];
        }
        else
        {
            decrypted[i] = cipher[i] ^ encryptBlock(previous, key);
            previous = cipher[i];
        }
    }

    printf("\n\nDecrypted plaintext:\n");

    for (int i = 0; i < n; i++)
        printf("%02X ", decrypted[i]);

    printf("\n");

    return 0;
}
