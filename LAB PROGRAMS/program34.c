
#include <stdio.h>

#define BLOCK_SIZE 8
#define MASK 255

// Educational 8-bit block transformation.
// Not a real secure block cipher.
unsigned char encryptBlock(unsigned char block,
                           unsigned char key)
{
    return (unsigned char)(((block ^ key) * 5 + 7) & MASK);
}

// Inverse transformation for decryption
unsigned char decryptBlock(unsigned char block,
                           unsigned char key)
{
    // Inverse of 5 modulo 256 is 205
    return (unsigned char)((((block - 7) * 205) & MASK) ^ key);
}

// ECB Encryption
void ecbEncrypt(unsigned char p[], unsigned char c[],
                int n, unsigned char key)
{
    for (int i = 0; i < n; i++)
        c[i] = encryptBlock(p[i], key);
}

// ECB Decryption
void ecbDecrypt(unsigned char c[], unsigned char p[],
                int n, unsigned char key)
{
    for (int i = 0; i < n; i++)
        p[i] = decryptBlock(c[i], key);
}

// CBC Encryption
void cbcEncrypt(unsigned char p[], unsigned char c[],
                int n, unsigned char key,
                unsigned char iv)
{
    unsigned char previous = iv;

    for (int i = 0; i < n; i++)
    {
        c[i] = encryptBlock(p[i] ^ previous, key);
        previous = c[i];
    }
}

// CBC Decryption
void cbcDecrypt(unsigned char c[], unsigned char p[],
                int n, unsigned char key,
                unsigned char iv)
{
    unsigned char previous = iv;

    for (int i = 0; i < n; i++)
    {
        p[i] = decryptBlock(c[i], key) ^ previous;
        previous = c[i];
    }
}

// CFB Encryption
void cfbEncrypt(unsigned char p[], unsigned char c[],
                int n, unsigned char key,
                unsigned char iv)
{
    unsigned char previous = iv;

    for (int i = 0; i < n; i++)
    {
        unsigned char stream = encryptBlock(previous, key);

        c[i] = p[i] ^ stream;
        previous = c[i];
    }
}

// CFB Decryption
void cfbDecrypt(unsigned char c[], unsigned char p[],
                int n, unsigned char key,
                unsigned char iv)
{
    unsigned char previous = iv;

    for (int i = 0; i < n; i++)
    {
        unsigned char stream = encryptBlock(previous, key);

        p[i] = c[i] ^ stream;
        previous = c[i];
    }
}

// Print byte array
void display(char label[], unsigned char data[], int n)
{
    printf("%s", label);

    for (int i = 0; i < n; i++)
        printf("%02X ", data[i]);

    printf("\n");
}

int main()
{
    unsigned char plaintext[BLOCK_SIZE];
    unsigned char ciphertext[BLOCK_SIZE];
    unsigned char decrypted[BLOCK_SIZE];

    unsigned char key, iv;
    int n;

    printf("ECB, CBC AND CFB MODES\n");

    printf("\nEnter number of complete blocks (1-8): ");
    scanf("%d", &n);

    if (n < 1 || n > BLOCK_SIZE)
    {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    printf("Enter key (0-255): ");
    scanf("%hhu", &key);

    printf("Enter IV (0-255): ");
    scanf("%hhu", &iv);

    printf("\nEnter plaintext bytes (0-255):\n");

    for (int i = 0; i < n; i++)
        scanf("%hhu", &plaintext[i]);

    display("\nPlaintext: ", plaintext, n);

    // ECB
    printf("\n--- ECB MODE ---\n");

    ecbEncrypt(plaintext, ciphertext, n, key);
    display("Ciphertext: ", ciphertext, n);

    ecbDecrypt(ciphertext, decrypted, n, key);
    display("Decrypted : ", decrypted, n);

    // CBC
    printf("\n--- CBC MODE ---\n");

    cbcEncrypt(plaintext, ciphertext, n, key, iv);
    display("Ciphertext: ", ciphertext, n);

    cbcDecrypt(ciphertext, decrypted, n, key, iv);
    display("Decrypted : ", decrypted, n);

    // CFB
    printf("\n--- CFB MODE ---\n");

    cfbEncrypt(plaintext, ciphertext, n, key, iv);
    display("Ciphertext: ", ciphertext, n);

    cfbDecrypt(ciphertext, decrypted, n, key, iv);
    display("Decrypted : ", decrypted, n);

    return 0;
}
