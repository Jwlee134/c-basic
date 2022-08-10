#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char *name;
    int age;
    char *personality;
    int level;
} Cat;

int collection[5] = {0, 0, 0, 0, 0};

Cat cats[5];

void initCats();
void printCat(int selected);
int checkCollection();

int main()
{
    srand(time(NULL));
    initCats();
    while (1)
    {
        printf("두근두근-! 어느 고양이의 집사가 될까요?\n아무 키나 눌러서 확인하세요!");
        getchar();

        int selected = rand() % 5;
        printCat(selected);
        collection[selected] = 1;

        int collectedAll = checkCollection();
        if (collectedAll)
        {
            break;
        }
    }
    return 0;
}

void initCats()
{
    cats[0].name = "깜냥이";
    cats[0].age = 5;
    cats[0].personality = "온순함";
    cats[0].level = 1;
    cats[1].name = "귀요미";
    cats[1].age = 10;
    cats[1].personality = "날카로움";
    cats[1].level = 2;
    cats[2].name = "수줍이";
    cats[2].age = 8;
    cats[2].personality = "늘 잠만잠";
    cats[2].level = 3;
    cats[3].name = "까꿍이";
    cats[3].age = 3;
    cats[3].personality = "시끄러움";
    cats[3].level = 4;
    cats[4].name = "돼냥이";
    cats[4].age = 1;
    cats[4].personality = "까칠함";
    cats[4].level = 5;
}

void printCat(int selected)
{
    printf("\n\n당신은 이 고양이의 집사가 되었어요!\n\n");
    printf("이름: %s\n", cats[selected].name);
    printf("나이: %d\n", cats[selected].age);
    printf("성격: %s\n", cats[selected].personality);
    printf("레벨: ");
    for (int i = 0; i < cats[selected].level; i++)
    {
        printf("*");
    }
    printf("\n\n");
}

int checkCollection()
{
    int collectedAll = 1;
    printf("\n\n현재 보유한 고양이 목록\n\n");
    for (int i = 0; i < 5; i++)
    {
        if (collection[i] == 0)
        {
            printf("%10s", "(빈 박스)");
            collectedAll = 0;
        }
        else
        {
            printf("%10s", cats[i].name);
        }
    }
    printf("\n\n");

    if (collectedAll)
    {
        printf("\n\n축하합니다! 모든 고양이를 다 모았습니다.\n\n");
    }

    return collectedAll;
}