
#include <stdio.h>

#define STATE_SIZE 1600
#define RATE_SIZE 1024
#define CAPACITY_SIZE (STATE_SIZE - RATE_SIZE)
#define LANE_SIZE 64

int main()
{
    int capacityLanes = CAPACITY_SIZE / LANE_SIZE;
    int blocks;

    // Initially all capacity lanes are zero
    int capacity[9] = {0};

    printf("SHA-3 CAPACITY LANE DEMONSTRATION\n");

    printf("\nState size       = %d bits\n", STATE_SIZE);
    printf("Rate size        = %d bits\n", RATE_SIZE);
    printf("Capacity size    = %d bits\n", CAPACITY_SIZE);
    printf("Lane size        = %d bits\n", LANE_SIZE);
    printf("Capacity lanes   = %d\n", capacityLanes);

    printf("\nEnter number of input blocks: ");
    scanf("%d", &blocks);

    if (blocks < 0)
    {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    printf("\nIgnoring permutation step...\n");

    // Input blocks affect only the rate portion.
    // Capacity lanes remain unchanged.
    for (int i = 0; i < blocks; i++)
    {
        printf("Processing input block %d...\n", i + 1);
    }

    printf("\nCapacity lane values:\n");

    for (int i = 0; i < capacityLanes; i++)
    {
        printf("Lane %d = %d\n", i + 1, capacity[i]);
    }

    printf("\nConclusion:\n");
    printf("All capacity lanes remain zero.\n");
    printf("No finite number of blocks can make them nonzero\n");
    printf("when the permutation step is ignored.\n");

    return 0;
}
