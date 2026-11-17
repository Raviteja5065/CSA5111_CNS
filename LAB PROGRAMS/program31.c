
#include <stdio.h>
#include <stdint.h>

// Generate CMAC subkey for 64-bit blocks
uint64_t generateSubkey64(uint64_t input)
{
    uint64_t Rb = 0x1B;

    if (input & 0x8000000000000000ULL)
    {
        return (input << 1) ^ Rb;
    }

    return input << 1;
}

// Generate CMAC subkey for 128-bit blocks
typedef struct
{
    uint64_t high;
    uint64_t low;
} Block128;

Block128 generateSubkey128(Block128 input)
{
    Block128 result;

    uint64_t Rb = 0x87;

    int msb = (input.high >> 63) & 1;

    // Shift the 128-bit value left by one
    result.high = (input.high << 1) | (input.low >> 63);
    result.low = input.low << 1;

    // XOR reduction constant when MSB is 1
    if (msb)
    {
        result.low ^= Rb;
    }

    return result;
}

int main()
{
    uint64_t L64, K1_64, K2_64;

    Block128 L128, K1_128, K2_128;

    printf("CMAC SUBKEY GENERATION\n");

    // 64-bit example
    L64 = 0x8000000000000000ULL;

    K1_64 = generateSubkey64(L64);
    K2_64 = generateSubkey64(K1_64);

    printf("\n64-BIT BLOCK SIZE\n");

    printf("L  = %016llX\n",
           (unsigned long long)L64);

    printf("K1 = %016llX\n",
           (unsigned long long)K1_64);

    printf("K2 = %016llX\n",
           (unsigned long long)K2_64);

    // 128-bit example
    L128.high = 0x8000000000000000ULL;
    L128.low  = 0x0000000000000000ULL;

    K1_128 = generateSubkey128(L128);
    K2_128 = generateSubkey128(K1_128);

    printf("\n128-BIT BLOCK SIZE\n");

    printf("L  = %016llX%016llX\n",
           (unsigned long long)L128.high,
           (unsigned long long)L128.low);

    printf("K1 = %016llX%016llX\n",
           (unsigned long long)K1_128.high,
           (unsigned long long)K1_128.low);

    printf("K2 = %016llX%016llX\n",
           (unsigned long long)K2_128.high,
           (unsigned long long)K2_128.low);

    return 0;
}
