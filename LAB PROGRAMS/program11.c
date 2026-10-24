#include <stdio.h>
#include <math.h>

int main() {
    double keys = 1.0;
    int i;

    for (i = 1; i <= 25; i++)
        keys *= i;

    printf("Possible Playfair keys: %.0f\n", keys);
    printf("Approximate key space: 2^%.2f\n",
           log(keys) / log(2.0));

    printf("Approximate effective keys after "
           "dividing by 25: %.0f\n", keys / 25.0);

    printf("Effective key space: 2^%.2f\n",
           log(keys / 25.0) / log(2.0));

    return 0;
}