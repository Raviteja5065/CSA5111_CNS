#include <stdio.h>

int main() {
    printf("ECB MODE\n");
    printf("Error in C1 affects only P1.\n");
    printf("P2 and subsequent blocks remain unaffected.\n\n");

    printf("CBC MODE: Error in transmitted C1\n");
    printf("P1: Corrupted.\n");
    printf("P2: Corresponding bit is flipped.\n");
    printf("P3 onwards: Unaffected by this isolated error.\n\n");

    printf("CBC MODE: Error in source plaintext P1\n");
    printf("C1 and all subsequent ciphertext blocks change.\n");
    printf("At the receiver, P1 and subsequent plaintext blocks\n");
    printf("may be corrupted because chaining is affected.\n");

    return 0;
}