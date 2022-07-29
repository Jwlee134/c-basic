#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum OPERATIONS
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
};

int calc(int a, int b, enum OPERATIONS x)
{
    switch (x)
    {
    case PLUS:
        return a + b;
    case MINUS:
        return a - b;
    case MULTIPLY:
        return a * b;
    case DIVIDE:
        return a / b;
    default:
        return 0;
    }
}

int getRandomNum(int count)
{
    return rand() % (count * 10) + 1;
}

void showQuestion(int level, int a, int b)
{
    printf("level %d: %d x %d = \n", level, a, b);
}

int main()
{
    srand(time(NULL));
    for (int i = 1; i < 6; i++)
    {
        int num1 = getRandomNum(i);
        int num2 = getRandomNum(i);
        int result = calc(num1, num2, MULTIPLY);
        int answer;
        showQuestion(i, num1, num2);
        scanf("%d", &answer);
        if (result == answer)
        {
            continue;
        }
        else
        {
            break;
        }
    }

    return 0;
}
