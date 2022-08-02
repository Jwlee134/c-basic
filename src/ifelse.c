#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ifelse()
{
    srand(time(NULL));             // Initialization, should only be called once.
    int random = rand() % 100 + 1; // Returns a pseudo-random integer between 0 and RAND_MAX.
    int chance = 10;
    int input;

    while (1)
    {
        printf("남은 기회는 %d번 입니다. 숫자를 입력하세요: ", chance--);
        scanf("%d", &input);

        if (chance == 0)
        {
            printf("남은 기회가 없습니다. 게임을 종료합니다.\n");
            break;
        }
        if (input == random)
        {
            printf("성공! 게임을 종료합니다.\n");
            break;
        }
        else if (input > random)
        {
            printf("Down!\n");
            continue;
        }
        else
        {
            printf("Up!\n");
            continue;
        }
    }

    return 0;
}
