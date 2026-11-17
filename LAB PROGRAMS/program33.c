
#include <stdio.h>
#include <stdint.h>

// Initial Permutation
int IP[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};

// Final Permutation
int FP[64] = {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

// Expansion table
int E[48] = {
32,1,2,3,4,5,
4,5,6,7,8,9,
8,9,10,11,12,13,
12,13,14,15,16,17,
16,17,18,19,20,21,
20,21,22,23,24,25,
24,25,26,27,28,29,
28,29,30,31,32,1
};

// Permutation P
int P[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};

// Permuted Choice 1
int PC1[56] = {
57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4
};

// Permuted Choice 2
int PC2[48] = {
14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32
};

// Left shifts
int shifts[16] = {
1,1,2,2,2,2,2,2,
1,2,2,2,2,2,2,1
};

// DES S-boxes
int S[8][4][16] = {
{
{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
},
{
{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
},
{
{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
},
{
{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
},
{
{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
},
{
{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
},
{
{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
},
{
{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
}
};

// Generic permutation function
uint64_t permute(uint64_t input, int *table,
                 int outputBits, int inputBits)
{
    uint64_t output = 0;

    for (int i = 0; i < outputBits; i++)
    {
        output <<= 1;
        output |= (input >> (inputBits - table[i])) & 1ULL;
    }

    return output;
}

// Generate 16 round keys
void generateKeys(uint64_t key, uint64_t roundKeys[16])
{
    uint64_t permKey = permute(key, PC1, 56, 64);

    uint32_t C = (permKey >> 28) & 0x0FFFFFFF;
    uint32_t D = permKey & 0x0FFFFFFF;

    for (int i = 0; i < 16; i++)
    {
        int shift = shifts[i];

        C = ((C << shift) | (C >> (28 - shift))) & 0x0FFFFFFF;
        D = ((D << shift) | (D >> (28 - shift))) & 0x0FFFFFFF;

        uint64_t combined = ((uint64_t)C << 28) | D;

        roundKeys[i] = permute(combined, PC2, 48, 56);
    }
}

// DES round function
uint32_t feistel(uint32_t R, uint64_t key)
{
    uint64_t expanded = permute(R, E, 48, 32);

    expanded ^= key;

    uint32_t output = 0;

    for (int i = 0; i < 8; i++)
    {
        int sixBits = (expanded >> (42 - 6 * i)) & 0x3F;

        int row = ((sixBits & 0x20) >> 4) |
                  (sixBits & 1);

        int col = (sixBits >> 1) & 0x0F;

        output = (output << 4) | S[i][row][col];
    }

    return (uint32_t)permute(output, P, 32, 32);
}

// DES encryption/decryption
uint64_t DES(uint64_t block, uint64_t key, int decrypt)
{
    uint64_t roundKeys[16];

    generateKeys(key, roundKeys);

    uint64_t permBlock = permute(block, IP, 64, 64);

    uint32_t L = (uint32_t)(permBlock >> 32);
    uint32_t R = (uint32_t)permBlock;

    for (int i = 0; i < 16; i++)
    {
        uint32_t temp = R;

        int index = decrypt ? 15 - i : i;

        R = L ^ feistel(R, roundKeys[index]);
        L = temp;
    }

    uint64_t combined = ((uint64_t)R << 32) | L;

    return permute(combined, FP, 64, 64);
}

int main()
{
    uint64_t plaintext, key;
    uint64_t ciphertext, decrypted;

    printf("Enter 64-bit plaintext (hex): ");
    scanf("%llx", (unsigned long long *)&plaintext);

    printf("Enter 64-bit key (hex): ");
    scanf("%llx", (unsigned long long *)&key);

    ciphertext = DES(plaintext, key, 0);
    decrypted = DES(ciphertext, key, 1);

    printf("\nDES ENCRYPTION\n");
    printf("Plaintext  : %016llX\n",
           (unsigned long long)plaintext);
    printf("Key        : %016llX\n",
           (unsigned long long)key);
    printf("Ciphertext : %016llX\n",
           (unsigned long long)ciphertext);

    printf("\nDES DECRYPTION\n");
    printf("Decrypted  : %016llX\n",
           (unsigned long long)decrypted);

    return 0;
}
