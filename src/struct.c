#include <stdio.h>

struct GameInfo
{
    char *name;
    int year;
    int price;
    char *company;

    struct GameInfo *friendGame;
};

typedef struct
{
    char *name;
    int year;
    int price;
    char *company;

    struct GameInfo *friendGame;
} GAME_INFO;

int main()
{
    struct GameInfo gameInfo1;

    gameInfo1.name = "나도게임";
    gameInfo1.year = 2017;
    gameInfo1.price = 50;
    gameInfo1.company = "나도회사";

    printf("\n--게임 출시 정보--\n");
    printf("게임명: %s\n", gameInfo1.name);
    printf("발매년도: %d\n", gameInfo1.year);
    printf("가격: %d\n", gameInfo1.price);
    printf("제작사: %s\n", gameInfo1.company);

    // 구조체를 배열처럼 초기화
    struct GameInfo gameInfo2 = {"너도게임", 2017, 100, "너도회사"};
    printf("\n--게임 출시 정보--\n");
    printf("게임명: %s\n", gameInfo2.name);
    printf("발매년도: %d\n", gameInfo2.year);
    printf("가격: %d\n", gameInfo2.price);
    printf("제작사: %s\n", gameInfo2.company);

    // 구조체 배열
    struct GameInfo gameArray[2] = {{"나도게임", 2017, 100, "나도회사"}, {"너도게임", 2017, 100, "너도회사"}};

    // 구조체 포인터
    struct GameInfo *gamePtr = &gameInfo1;
    printf("\n--미션맨의 게임 출시 정보--\n");
    /* printf("게임명: %s\n", (*gamePtr).name);
    printf("발매년도: %d\n", (*gamePtr).year);
    printf("가격: %d\n", (*gamePtr).price);
    printf("제작사: %s\n", (*gamePtr).company); */

    printf("게임명: %s\n", gamePtr->name);
    printf("발매년도: %d\n", gamePtr->year);
    printf("가격: %d\n", gamePtr->price);
    printf("제작사: %s\n", gamePtr->company);

    // 구조체 내의 구조체
    gameInfo1.friendGame = &gameInfo2;

    printf("\n--연관업체 게임 출시 정보--\n");
    printf("게임명: %s\n", gameInfo1.friendGame->name);
    printf("발매년도: %d\n", gameInfo1.friendGame->year);
    printf("가격: %d\n", gameInfo1.friendGame->price);
    printf("제작사: %s\n", gameInfo1.friendGame->company);

    // typedef: 자료형에 별명 지정
    int i = 1;
    typedef int 정수;
    typedef float 실수;
    정수 정수변수 = 3;     // int i = 3;
    실수 실수변수 = 3.23f; // float f = 3.23f;

    printf("\n정수변수 : %d, 실수변수 : %.2f\n\n", 정수변수, 실수변수);

    typedef struct GameInfo 게임정보;
    게임정보 game1 = {"한글 게임", 2015, 50, "게임회사"};

    GAME_INFO game2 = {"한글 게임2", 2014, 100, "게임회사"};

    return 0;
}
