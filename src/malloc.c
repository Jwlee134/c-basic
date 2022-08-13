#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int *p;

    // 반환 타입은 타입이 없는 주소(void *)이므로 정수들을 저장하기 위해 int *로 변환(선택사항)
    // 인자로 들어가는 숫자는 할당받을 메모리의 크기의 byte
    p = (int *)malloc(10 * sizeof(int));
    if (p == NULL)
    {
        printf("동적 메모리 할당 실패");
    }

    p[0] = 12;
    p[1] = 24;
    *(p + 2) = 36;

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", p[i]); // 12 24 36 0 0 ...
    }

    // 배열의 크기를 키울 때 (다른 메모리 공간에 더 큰 공간을 할당받고 원래의 배열의 원소들을 새로운 곳으로 옮겨옴)
    int *arr = (int *)malloc(4 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    *(arr + 2) = 3;

    int *temp = (int *)malloc(8 * sizeof(int));
    for (int i = 0; i < 4; i++)
    {
        temp[i] = arr[i];
    }
    // arr는 이제 temp의 주소를 참조함
    arr = temp;

    arr[3] = 4;
    arr[4] = 5;

    // arr가 16 -> 32byte 크기로 변경됨
    for (int i = 0; i < 8; i++)
    {
        printf("%d\n", arr[i]); // 1 2 3 4 5 0 0 0
    }

    // 그럼 이제 원래 arr가 가지던 16byte의 공간의 처리는?

    /*
        int *arr = (int *)malloc(4 * sizeof(int));
        int arr[4]

        1번과 2번의 차이
        1. 위 아래 둘 다 배열의 시작 주소를 저장하는 포인터 변수이지만 아래는 재할당이 불가능하다.
        2. Later
     */

    return 0;
}
