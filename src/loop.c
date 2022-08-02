#include <stdio.h>

int loop()
{
    /* for (int i = 0; i < 10; i++)
    {
        printf("Hello for\n");
    }

    int i = 0;
    while (i < 10)
    {
        printf("Hello while\n");
        i++;
    }

    int j = 0;
    do
    {
        printf("Hello dowhile\n");
        j++;
    } while (j < 10); */

    int floor;
    printf("피라미드는 몇 층인가? ");
    scanf("%d", &floor);

    for (int i = 0; i < floor; i++)
    {
        for (int j = 0; j < floor - i - 1; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i * 2 + 1; k++)
        {
            printf("*");
        }

        printf("\n");
    }

    return 0;
}
