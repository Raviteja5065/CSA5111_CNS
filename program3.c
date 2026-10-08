#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[])
{
    int used[26] = {0};
    int row = 0, col = 0;
    int i, j;
    char ch;

    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A'])
        {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;

            if (col == 5)
            {
                col = 0;
                row++;
            }
        }
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char a, char b, char *x, char *y)
{
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2)
    {
        *x = matrix[r1][(c1 + 1) % 5];
        *y = matrix[r2][(c2 + 1) % 5];
    }
    else if (c1 == c2)
    {
        *x = matrix[(r1 + 1) % 5][c1];
        *y = matrix[(r2 + 1) % 5][c2];
    }
    else
    {
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

int main()
{
    char key[100];
    char plaintext[200];
    char prepared[200];
    char ciphertext[200];

    int i, j = 0;
    int length;

    printf("Enter the keyword: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    generateMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    /* Prepare plaintext */
    j = 0;

    for (i = 0; plaintext[i] != '\0'; i++)
    {
        char ch = toupper(plaintext[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z')
        {
            if (j > 0 && prepared[j - 1] == ch)
            {
                prepared[j++] = 'X';
            }

            prepared[j++] = ch;
        }
    }

    if (j % 2 != 0)
    {
        prepared[j++] = 'X';
    }

    prepared[j] = '\0';
    length = j;

    j = 0;

    for (i = 0; i < length; i += 2)
    {
        encryptPair(
            prepared[i],
            prepared[i + 1],
            &ciphertext[j],
            &ciphertext[j + 1]
        );

        j += 2;
    }

    ciphertext[j] = '\0';

    printf("\nPrepared Plaintext: %s", prepared);
    printf("\nCiphertext: %s\n", ciphertext);

    return 0;
}