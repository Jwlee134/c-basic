#include <stdio.h>

int main(void)
{
    // 정수
    int age = 12;
    printf("%d\n", age); // %d는 정수 출력, 두 번째 인자 age가 %d 자리에 들어감
    age = 13;
    printf("%d\n", age);
    printf("%d * %d = %d\n", 532, 453, 532 * 453);

    // 실수
    float f = 65.5f;     // f 붙여야 함
    printf("%.1f\n", f); // %f는 float 출력, 중간 소수점은 ~까지 출력할 소수점 자리
    double d = 4.428;
    printf("%.2lf\n", d); // %f는 double 출력

    // 상수
    const YEAR = 1997;
    printf("태어난 년도 : %d\n", YEAR);

    int input;
    printf("값을 입력하세요. : ");
    scanf("%d", &input); // 정수를 받고 input이라는 변수의 메모리 주소에 값을 넣겠다
    printf("입력값 : %d\n", input);

    int one, two, three;
    printf("세 개의 정수를 입력하세요 : ");
    scanf("%d %d %d", &one, &two, &three);
    printf("입력값 : %d %d %d\n", one, two, three);

    // 문자, 문자열
    char c = 'A';
    printf("%c\n", c);

    char str[256];    // 문자열 길이 256자
    scanf("%s", str); // 문자열은 & 붙일 필요 없음
    printf("%s\n", str);

    char name[256];
    printf("이름: ");
    scanf("%s", name);

    int age;
    printf("나이: ");
    scanf("%d", &age);

    float weight;
    printf("몸무게: ");
    scanf("%f", &weight);

    double height;
    printf("키: ");
    scanf("%lf", &height);

    char crime[256];
    printf("저지른 범죄: ");
    scanf("%s", crime);

    printf("\n\n--- 범죄자 정보 ---\n\n");
    printf("이름: %s\n", name);
    printf("나이: %d\n", age);
    printf("몸무게: %.1f\n", weight);
    printf("키: %.1lf\n", height);
    printf("범죄: %s\n", crime);

    return 0;
}
