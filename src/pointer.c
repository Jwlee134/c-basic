#include <stdio.h>
#include <time.h>

/* void swap(int a, int b);
void swap_addr(int *a, int *b);
void changeArr(int *ptr); */

void printFishes(int *ptr);
void decreaseWater(long recentDuration);
int allDied();

long startTime = 0,
     totalDuration = 0,
     recentDuration = 0;
int level = 1,
    fishes[6] = {100, 100, 100, 100, 100, 100},
    *ptr = fishes;

int main()
{
    /* // 포인터는 다른 변수의 메모리 주솟값을 값으로 저장하는 변수
    int n1 = 1;
    int n2 = 2;
    int *p1 = &n1;
    int *p2 = &n2;
    printf("%p\n", p1);
    printf("%p\n", p2);

    // Dereference, 포인터가 가리키는 변수의 값을 가져옴, * = Dereference operator
    printf("%d\n", *p1); // 1
    printf("%d\n", *p2); // 2

    // 포인터를 통해 변수 값 재할당
    *p2 = *p2 * 3;      // n2 = n2 * 3
    printf("%d\n", n2); // 6

    // 동일한 주솟값을 참조하는 다른 포인터로 변수 값 재할당
    int *p3 = &n2;
    *p3 = *p3 * 3;      // n2 = n2 * 3
    printf("%d\n", n2); // 18

    // 포인터 변수의 메모리 주소
    printf("%p\n", p1);

    // 포인터의 값을 바꿈에 따라 배열도 바뀜
    int arr[3] = {5, 10, 15};
    int *ptr = arr;
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", arr[i]); // 5, 10, 15
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", ptr[i]); // 5, 10, 15
    }
    ptr[0] = 100;
    ptr[1] = 200;
    ptr[2] = 300;
    // *(arr + i) == arr[i] => 배열은 메모리에 연속적으로 저장되므로 이런식으로 표현이 가능
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", *(arr + i)); // 100, 200, 300
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", *(ptr + i)); // 100, 200, 300
    }
    // arr == arr 배열의 첫 번째 값의 주소(arr[0])
    printf("arr 자체의 주소: %p\n", arr);
    printf("arr[0]의 주소: %p\n", &arr[0]);
    // arr 자체는 주소값을 가지므로 그것의 실제 값을 출력
    printf("arr 자체의 주소에 있는 값: %d\n", *arr);
    printf("arr[0]의 실제 값: %d\n", *&arr[0]);

    // &는 reference operator, 주소 값을 가져오는 연산자
    // *는 dereference operator, 실제 값을 가져오는 연산자

    // 함수에 값만 넘기면?
    int a = 10, b = 20;
    printf("함수 밖 a의 주소: %p\n", &a);
    printf("함수 밖 b의 주소: %p\n", &b);
    printf("swap 전: %d, %d\n", a, b); // 10, 20
    swap(a, b);
    printf("swap 후: %d, %d\n", a, b); // 10, 20

    // 함수에 메모리 주솟값을 넘기면?
    printf("swap_addr 전: %d, %d\n", a, b); // 10, 20
    swap_addr(&a, &b);
    printf("swap_addr 후: %d, %d\n", a, b); // 20, 10

    int arr2[3] = {10, 20, 30};
    changeArr(arr2);
    changeArr(&arr2[0]);
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", arr2[i]);
    } */

    startTime = clock(); // 현재 시간을 millisec로 반환

    while (1)
    {
        printFishes(ptr);

        int input;
        printf("몇 번 어항에 물을 주시겠어요? ");
        scanf("%d", &input);

        totalDuration = (clock() - startTime) / 1000;
        recentDuration = totalDuration - recentDuration;
        printf("총 경과 시간: %ld초\n", totalDuration);
        printf("최근 경과 시간: %ld초\n", recentDuration);

        decreaseWater(recentDuration);

        if (input < 1 || input > 6)
        {
            continue;
        }

        printf("%d번 어항에 물을 줍니다.\n", input);

        if (ptr[input - 1] == 0)
        {
            printf("%d번 물고기는 이미 죽었습니다.. 물을 주지 않습니다.\n", input);
        }
        else if (ptr[input - 1] < 100)
        {

            ptr[input - 1] += 1;
        }

        if (totalDuration / 20 > level - 1)
        {
            level++;
            printf("*** 축 레벨 업! 기존 %d 레벨에서 %d 레벨로 업그레이드! ***\n", level - 1, level);
            if (level == 5)
            {
                printf("\n\n축하합니다! 최고 레벨을 달성하였습니다. 게임을 종료합니다.\n\n");
                break;
            }
        }
        if (allDied())
        {
            printf("모든 물고기가.. ㅠㅠ 흑흑..\n");
            break;
        }
        else
        {
            printf("물고기가 아직 살아 있어요!\n");
        }
        recentDuration = totalDuration;
    }

    return 0;
}

void printFishes(int *ptr)
{
    printf("\n%2d번%2d번%2d번%2d번%2d번%2d번\n", 1, 2, 3, 4, 5, 6);
    for (int i = 0; i < 6; i++)
    {
        printf(" %d", ptr[i]);
    }
    printf("\n\n");
}

void decreaseWater(long recentDuration)
{
    for (int i = 0; i < 6; i++)
    {
        ptr[i] = ptr[i] - (level * recentDuration);
        if (ptr[i] < 0)
        {
            ptr[i] = 0;
        }
    }
}

int allDied()
{
    for (int i = 0; i < 6; i++)
    {
        if (ptr[i] > 0)
            return 0;
    }
    return 1;
}

/* void swap(int a, int b)
{
    printf("함수 내 a의 주소: %p\n", &a);
    printf("함수 내 b의 주소: %p\n", &b);
    int temp = a;
    a = b;
    b = temp;
    printf("swap 내: %d, %d\n", a, b); // 20, 10
}

void swap_addr(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void changeArr(int *ptr)
{
    ptr[2] = 50;
} */