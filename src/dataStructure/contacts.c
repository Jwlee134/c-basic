#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define COMMAND 50

#define INIT_CAPACITY 3
#define SEPERATOR " "

/*
    전역번수
    - 함수의 외부에 선언된 변수
    - 프로그램 시작 시 메모리가 할당되고 프로그램이 종료될 때 까지 유지
    - Data section이라고 부르는 메모리 영역에 위치

    지역변수
    - 함수의 내부에 선언된 변수들
    - 부모 함수가 호출될 때 메모리가 할당되고 함수 종료 시 소멸
    - Stack이라고 부르는 영역에 위치


    c는 문자열의 끝을 \0로 인식하기 때문에 strtok은 원본 문자열을 수정한다.(구분자를 \0로 대체한다.)
    따라서 char *str로 선언된 문자열(string literal)은 strtok을 사용하면 오류가 발생한다.
 */

// 배열 재할당을 위해 크기를 정해주지 않고 포인터로 선언
char **names;
char **numbers;
int num_of_people = 0;
int capacity = INIT_CAPACITY;

void init_directory();
void process_command();
int read_line(char str[], int limit);
void add(char *name, char *number);
void reallocate();
void find(char *name);
void status();
void remove_person(char *name);
void load(char *filename);
void save(char *filename);
int search(char *name);

int main(void)
{
    init_directory();
    process_command();

    return 0;
}

void init_directory()
{
    // INIT_CAPACITY 칸 만큼 생성
    names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPACITY * sizeof(char *));
}

void process_command()
{
    char command_line[COMMAND];
    char *command, *arg1, *arg2;

    while (1)
    {
        printf("$ ");
        if (read_line(command_line, COMMAND) <= 0)
        {
            continue;
        }
        command = strtok(command_line, SEPERATOR);
        if (!strcmp(command, "add"))
        {
            arg1 = strtok(NULL, SEPERATOR);
            if (arg1 == NULL)
            {
                printf("User name required.\n");
                continue;
            }
            arg2 = strtok(NULL, SEPERATOR);
            if (arg2 == NULL)
            {
                printf("Phone number required.\n");
                continue;
            }
            add(arg1, arg2);
            printf("%s was added successfully.\n", arg1);
        }
        else if (!strcmp(command, "find"))
        {
            arg1 = strtok(NULL, SEPERATOR);
            if (arg1 == NULL)
            {
                printf("Invalid arguments.\n");
                continue;
            }
            find(arg1);
        }
        else if (!strcmp(command, "status"))
        {
            status();
        }
        else if (!strcmp(command, "remove"))
        {
            arg1 = strtok(NULL, SEPERATOR);
            if (arg1 == NULL)
            {
                printf("Invalid arguments.\n");
                continue;
            }
            remove_person(arg1);
        }
        else if (!strcmp(command, "read"))
        {
            arg1 = strtok(NULL, SEPERATOR);
            if (arg1 == NULL)
            {
                printf("Filename required.\n");
                continue;
            }
            load(arg1);
        }
        else if (!strcmp(command, "save"))
        {
            arg1 = strtok(NULL, SEPERATOR);
            if (arg1 == NULL || strcmp("as", arg1))
            {
                printf("Missing 'as' keyword.\n");
                continue;
            }
            arg2 = strtok(NULL, SEPERATOR);
            if (arg2 == NULL)
            {
                printf("Filename required.\n");
                continue;
            }
            save(arg2);
        }
        else if (!strcmp(command, "exit"))
        {
            break;
        }
    }
}

int read_line(char str[], int limit)
{
    int ch, i = 0;
    // 줄바꿈 문자가 나올 때까지 str에 문자를 저장한다.
    while ((ch = getchar()) != '\n')
    {
        // 최대 길이 + null character를 넘지 않을때만 저장한다.
        if (i < limit - 1)
        {
            str[i++] = ch;
        }
    }
    str[i] = '\0';

    return i;
}

void add(char *name, char *number)
{
    if (num_of_people >= capacity)
    {
        reallocate();
    }
    /*
        strdup를 사용해야 하는 이유
        1. name과 number는 지역변수이므로 스택에 할당된 메모리이다. 즉 함수가 종료되면 소멸된다.
        따라서 문자열을 복제한 후 names와 numbers에 복제된 배열의 주소를 저장해야 하는데,
        strdup 함수로 복제된 배열의 메모리는 malloc으로 동적 할당되어 힙에 저장이 되고
        이는 add 함수가 종료된 뒤에도 사라지지 않는다.
        2. name과 number는 process_command의 arg1, arg2 포인터 변수이다.
        이 주소들을 names와 numbers에 그대로 저장하면 다른 커맨들르 입력하여 arg1, arg2가 변경될 때
        영향을 받게 된다.

        동적 메모리 할당
        - 아무때나 malloc등의 함수를 호출하여 필요한 크기의 메모리를 할당하는 방법
        - 힙(heap)이라고 부르는 영역에 위치한다.
        - 명시적으로 free() 함수를 호출하여 반환하지 않는 한 계속 유지된다.
     */

    // 사전식 순서로 나보다 큰 항목은 한 칸씩 뒤로 이동시키고 난 뒤 빈 자리에 삽입
    int i = num_of_people - 1;
    while (i >= 0 && strcmp(names[i], name) > 0)
    {
        names[i + 1] = names[i];
        numbers[i + 1] = numbers[i];
        i--;
    }

    names[i + 1] = strdup(name);
    numbers[i + 1] = strdup(number);
    num_of_people++;
}

void reallocate()
{
    // 크기가 2배인 배열들을 할당
    capacity *= 2;
    char **tmp1 = (char **)malloc(capacity * sizeof(char *));
    char **tmp2 = (char **)malloc(capacity * sizeof(char *));

    // 원본 배열에 있던 값들을 모두 새로운 배열에 복사
    for (int i = 0; i < num_of_people; i++)
    {
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }

    // 원본 배열의 내용들은 동적 메모리 할당으로 만들어졌으므로 없어지지 않음
    // 따라서 free 함수로 반환
    free(names);
    free(numbers);

    // names와 numbers가 새로운 배열의 주소를 가리키도록 설정 (배열의 이름은 포인터 변수)
    names = tmp1;
    numbers = tmp2;
}

void find(char *name)
{
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

void remove_person(char *name)
{
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

void load(char *filename)
{
    char name[COMMAND], number[COMMAND];

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
        add(name, number);
    }
    fclose(fp);
    printf("File has been loaded successfully.\n");
}

void save(char *filename)
{
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