#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main() {
    unsigned char key[24] = "123456789012345678901234";
    unsigned char iv[8] = "12345678";
    unsigned char plaintext[] = "HELLO CRYPTOGRAPHY";
    unsigned char ciphertext[128];

    EVP_CIPHER_CTX *ctx;
    int len, total = 0, i;

    ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        printf("Context creation failed.\n");
        return 1;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(),
                           NULL, key, iv) != 1) {
        printf("3DES initialization failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    if (EVP_EncryptUpdate(ctx, ciphertext, &len,
                          plaintext,
                          strlen((char *)plaintext)) != 1) {
        printf("Encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    total = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + total,
                            &len) != 1) {
        printf("Final encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        return 1;
    }

    total += len;

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext (hex): ");

    for (i = 0; i < total; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    EVP_CIPHER_CTX_free(ctx);
    return 0;
}