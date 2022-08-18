#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define COMMAND 20

/*
    전역번수
    - 함수의 외부에 선언된 변수
    - 프로그램 시작 시 메모리가 할당되고 프로그램이 종료될 때 까지 유지
    - Data section이라고 부르는 메모리 영역에 위치

    지역변수
    - 함수의 내부에 선언된 변수들
    - 부모 함수가 호출될 때 메모리가 할당되고 함수 종료 시 소멸
    - Stack이라고 부르는 영역에 위치
 */

char *names[CAPACITY];
char *numbers[CAPACITY];
int num_of_people = 0;

void add();
void find();
void status();
void remove_person();
void load();
void save();
int search(char *name);

int main(void)
{
    char command[COMMAND];
    while (1)
    {
        printf("$ ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0)
        {
            add();
        }
        else if (strcmp(command, "find") == 0)
        {
            find();
        }
        else if (strcmp(command, "status") == 0)
        {
            status();
        }
        else if (strcmp(command, "remove") == 0)
        {
            remove_person();
        }
        else if (strcmp(command, "read") == 0)
        {
            load();
        }
        else if (strcmp(command, "save") == 0)
        {
            save();
        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }

    return 0;
}

void add()
{
    char name[COMMAND], number[COMMAND];
    scanf("%s %s", name, number);
    /*
        strdup를 사용해야 하는 이유
        name과 number는 add 함수의 지역변수이므로 스택에 할당된 메모리이다. 즉 add 함수가 종료되면 소멸된다.
        따라서 문자열을 복제한 후 names와 numbers에 복제된 배열의 주소를 저장해야 하는데,
        strdup 함수로 복제된 배열의 메모리는 malloc으로 동적 할당되어 힙에 저장이 되고
        이는 add 함수가 종료된 뒤에도 사라지지 않는다.

        동적 메모리 할당
        - 아무때나 malloc등의 함수를 호출하여 필요한 크기의 메모리를 할당하는 방법
        - 힙(heap)이라고 부르는 영역에 위치한다.
        - 명시적으로 free() 함수를 호출하여 반환하지 않는 한 계속 유지된다.
     */

    // 사전식 순서로 나보다 큰 항목은 한 칸씩 뒤로 이동시키고 난 뒤 빈 자리에 삽입
    int i = num_of_people - 1;
    while (i >= 0 && strcmp(name, names[i]) > 0)
    {
        names[i + 1] = names[i];
        numbers[i + 1] = numbers[i];
        i--;
    }

    names[i + 1] = strdup(name);
    numbers[i + 1] = strdup(number);
    num_of_people++;

    printf("%s was added successfully.\n", name);
}

void find()
{
    char name[COMMAND];
    scanf("%s", name);

    int index = search(name);
    if (index == -1)
    {
        printf("No person named '%s' exists.\n", name);
    }
    else
    {
        printf("%s\n", numbers[index]);
    }
}

void status()
{
    for (int i = 0; i < num_of_people; i++)
    {
        printf("%s %s\n", names[i], numbers[i]);
    }
    printf("Total %d persons.\n", num_of_people);
}

void remove_person()
{
    char name[COMMAND];
    scanf("%s", name);

    int index = search(name);
    if (index == -1)
    {
        printf("No person named '%s' exists.\n", name);
        return;
    }

    // 인덱스의 사람을 다음 인덱스의 사람으로 교체
    for (int i = index; i < num_of_people - 1; i++)
    {
        names[index] = names[index + 1];
        numbers[index] = numbers[index + 1];
    }
    num_of_people--;
    printf("'%s' was deleted successfully.\n", name);
}

void load()
{
    char filename[COMMAND], name[COMMAND], number[COMMAND];
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Cannot open the file.\n");
        return;
    }
    // 이름을 읽어와서 name 배열에 저장하면
    while ((fscanf(fp, "%s", name) != EOF))
    {
        fscanf(fp, "%s", number); // 전화번호를 읽어와서 number 배열에 저장한다.
        names[num_of_people] = strdup(name);
        numbers[num_of_people] = strdup(number);
        num_of_people++;
    }
    fclose(fp);
}

void save()
{
    char filename[COMMAND], temp[COMMAND];

    scanf("%s", temp); // as
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("File open failed.\n");
        return;
    }
    for (int i = 0; i < num_of_people; i++)
    {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
    }
    fclose(fp);
}

int search(char *name)
{
    for (int i = 0; i < num_of_people; i++)
    {
        if (!strcmp(names[i], name))
        {
            return i;
        }
    }
    return -1;
}