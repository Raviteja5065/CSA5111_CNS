#include <stdio.h>
#include <ctype.h>

int main()
{
    char text[100];
    int key, i;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the key (1-25): ");
    scanf("%d", &key);

    for (i = 0; text[i] != '\0'; i++)
    {
        if (isupper(text[i]))
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';

        else if (islower(text[i]))
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';
    }

    printf("Ciphertext: %s", text);

    return 0;
}