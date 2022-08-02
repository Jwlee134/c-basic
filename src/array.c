#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // 배열의 길이를 알고 있다면 사이즈를 넣어도 됨, 하지만 한 번 생성된 후에는 사이즈 변경 불가
    int array[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", array[i]);
    }
    float arrayf[5] = {1.0f, 2.0f, 3.0f};
    for (int i = 0; i < 5; i++)
    {
        printf("%.2f\n", arrayf[i]);
    }

    // c에서 string을 생셩하는 방법(c에서 string은 배열)
    char str[] = "coding";
    printf("%s\n", str);

    /*
    sizeof operator를 사용한 값을 출력할 때에는 %lu format specifier를 사용해야 한다.
    왜냐면 컴파일러가 sizeof operator를 사용할 때는 int(%d) 대신 long unsigned unit (%lu)
    을 반환하는 것을 기대하기 때문이다.
     */

    printf("%lu\n", sizeof(str)); // 7

    /*
    6이 아니라 7이 나오는 이유는 string끝에는 null termininating character라는 것이 있기 때문
    이는 c에게 여기가 string의 끝이라는 것을 알려줌
     */

    for (int i = 0; i < sizeof(str); i++)
    {
        printf("%c\n", str[i]);
    }

    // 한글은 2byte 또는 3byte, 맨 뒤 null 1byte = 13
    char kor[] = "나도코딩";
    printf("%s\n", kor);
    printf("%lu\n", sizeof(kor)); // 13

    // string을 생성하는 다른 방법, 이런 방법으로 생성할 경우 끝에 null termininating character 붙여야 함
    char carr[] = {'c', 'o', 'd', 'i', 'n', 'g', '\0'};
    printf("%s\n", carr);
    for (int i = 0; i < sizeof(carr); i++)
    {
        printf("%d\n", carr[i]); // string을 demical로 출력하면 ascii 코드 출력됨, null = 0
    }
    for (int i = 0; i < 128; i++)
    {
        printf("%d : %c\n", i, i);
    }

    srand(time(NULL));
    int answer;
    int treatment = rand() % 4; // 발모제(0 ~ 3)

    int numOfBottleToShow = 0;
    int prevNumOfBottleToShow = 0;

    for (int i = 0; i < 3; i++)
    {
        int bottles[4] = {0, 0, 0, 0};

        do
        {
            numOfBottleToShow = rand() % 2 + 2; // 2 ~ 3개의 발모제 투입
        } while (numOfBottleToShow == prevNumOfBottleToShow);

        printf("%d 번째 시도: ", i + 1);

        for (int j = 0; j < numOfBottleToShow; j++)
        {
            int randomNum = rand() % 4;
            if (bottles[randomNum] == 0)
            {
                bottles[randomNum] = 1;
            }
            else
            {
                j--;
                continue;
            }
        }

        for (int k = 0; k < 4; k++)
        {
            if (bottles[k] == 1)
            {
                printf("%d ", k);
            }
        }

        printf("번 발모제를 머리에 바릅니다.\n\n");

        if (bottles[treatment] == 1)
        {
            printf("성공! 머리가 났어요.\n");
        }
        else
        {
            printf("실패! 머리가 나지 않았어요.\n");
        }
        prevNumOfBottleToShow = numOfBottleToShow;
        getchar();
    }

    printf("발모제는 몇 번일까요? ");
    scanf("%d", &answer);

    if (answer == treatment)
    {
        printf("\n정답입니다.");
    }
    else
    {
        printf("\n정답이 아닙니다. 정답은 %d번 입니다.", treatment);
    }

    return 0;
}
