#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 100
#define COMMAND 50
#define SEPERATOR " "

typedef struct
{
    char *name;
    char *number;
    char *email;
    char *group;
} Person;
/*
    기존 v4에서는 구조체 배열 한 칸의 구조체가 변수들을 전부 담고 있었다.
    이렇게 되면 add나 remove 함수 호출 시 구조체 내의 모든 멤버들이 복사된다.
    또한 print_person 함수 호출 시에도 구조체 자체를 넘겨주므로 (call by value)
    구조체의 모든 멤버들이 새로 복사된다. (복사되는 데이터의 양이 많다.)
    이는 구조체 자체를 리턴하는 함수가 있을 때에도 마찬가지이다.

    따라서 구조체 배열이 아니라 구조체 포인터 배열로 선언하면
    배열은 구조체가 아니라 구조체의 포인터를 담게 되고
    위의 함수들을 호출할 때 모든 멤버들이 아니라 포인터만 복사되므로 효율성이 높아진다.
 */
Person *directory[CAPACITY];
int num_of_people = 0;

void process_command();
int read_line(FILE *fp, char str[], int limit);
void add(char *name, char *number, char *email, char *group);
void handle_add(char *name);
void find(char *name);
void status();
void remove_person(char *name);
void load(char *filename);
void save(char *filename);
int search(char *name);
int compose_name(char str[], int limit);
void print_person(Person *p);

int main(void)
{
    process_command();

    return 0;
}

void process_command()
{
    char command_line[COMMAND], name_str[COMMAND];
    char *command, *argument;

    while (1)
    {
        printf("$ ");
        if (read_line(stdin, command_line, COMMAND) <= 0)
        {
            continue;
        }
        // 첫 번째 strtok 호출(command)
        command = strtok(command_line, SEPERATOR);
        if (!strcmp(command, "add"))
        {
            if (!compose_name(name_str, COMMAND))
            {
                printf("Name is required.\n");
                continue;
            }
            handle_add(name_str);
            printf("%s was added successfully.\n", name_str);
        }
        else if (!strcmp(command, "find"))
        {
            if (!compose_name(name_str, COMMAND))
            {
                printf("Name is required.\n");
                continue;
            }
            find(name_str);
        }
        else if (!strcmp(command, "status"))
        {
            status();
        }
        else if (!strcmp(command, "remove"))
        {
            if (!compose_name(name_str, COMMAND))
            {
                printf("Name is required.\n");
                continue;
            }
            remove_person(name_str);
        }
        else if (!strcmp(command, "read"))
        {
            argument = strtok(NULL, SEPERATOR);
            if (argument == NULL)
            {
                printf("Filename required.\n");
                continue;
            }
            load(argument);
        }
        else if (!strcmp(command, "save"))
        {
            argument = strtok(NULL, SEPERATOR);
            if (argument == NULL || strcmp("as", argument))
            {
                printf("Missing 'as' keyword.\n");
                continue;
            }
            argument = strtok(NULL, SEPERATOR);
            if (argument == NULL)
            {
                printf("Filename required.\n");
                continue;
            }
            save(argument);
        }
        else if (!strcmp(command, "exit"))
        {
            break;
        }
    }
}

/*
    키보드 뿐만이 아니라 파일로부터도 읽을 수 있음
    fgetc(stdin) => 키보드 입력
 */
int read_line(FILE *fp, char str[], int limit)
{
    int ch, i = 0;
    // 줄바꿈 문자가 나올 때까지 str에 문자를 저장한다.
    // fgetc = getchar의 file 버전
    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
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

void add(char *name, char *number, char *email, char *group)
{
    int i = num_of_people - 1;
    while (i >= 0 && strcmp(directory[i]->name, name) > 0)
    {
        directory[i + 1] = directory[i];
        i--;
    }
    directory[i + 1]->name = strdup(name);
    directory[i + 1]->number = strdup(number);
    directory[i + 1]->email = strdup(email);
    directory[i + 1]->group = strdup(group);
    num_of_people++;
}

void handle_add(char *name)
{
    char number[COMMAND], email[COMMAND], group[COMMAND];
    char empty[] = " ";

    printf("Phone: ");
    read_line(stdin, number, COMMAND);
    printf("Email: ");
    read_line(stdin, email, COMMAND);
    printf("Group: ");
    read_line(stdin, group, COMMAND);

    add(name, (strlen(number) > 0 ? number : empty),
        (strlen(email) > 0 ? email : empty),
        (strlen(group) > 0 ? group : empty));
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
        print_person(directory[index]);
    }
}

void status()
{
    for (int i = 0; i < num_of_people; i++)
    {
        print_person(directory[i]);
    }
    printf("Total %d people.\n", num_of_people);
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
        directory[i] = directory[i + 1];
    }
    num_of_people--;
    printf("'%s' was deleted successfully.\n", name);
}

void load(char *filename)
{
    char buffer[COMMAND];
    char *name, *number, *email, *group;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Cannot open the file.\n");
        return;
    }
    while (1)
    {
        if (!read_line(fp, buffer, COMMAND))
        {
            break;
        }
        name = strtok(buffer, "#");
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(name, number, email, group);
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
        fprintf(fp, "%s#", directory[i]->name);
        fprintf(fp, "%s#", directory[i]->number);
        fprintf(fp, "%s#", directory[i]->email);
        fprintf(fp, "%s#\n", directory[i]->group);
    }
    fclose(fp);
    printf("File has been saved successfully.\n");
}

int search(char *name)
{
    for (int i = 0; i < num_of_people; i++)
    {
        if (!strcmp(directory[i]->name, name))
        {
            return i;
        }
    }
    return -1;
}

int compose_name(char str[], int limit)
{
    char *ptr;
    int length = 0;

    // 두 번째 strtok 호출(이름)
    ptr = strtok(NULL, " ");
    if (ptr == NULL)
    {
        return 0;
    }
    strcpy(str, ptr);
    length += strlen(ptr);

    while ((ptr = strtok(NULL, " ")) != NULL)
    {
        if (length + strlen(ptr) + 1 < limit)
        {
            str[length++] = ' ';
            str[length] = '\0';
            strcat(str, ptr);
            length += strlen(ptr);
        }
    }
    return length;
}

void print_person(Person *p)
{
    printf("%s:\n", p->name);
    printf("    Phone: %s\n", p->number);
    printf("    Email: %s\n", p->email);
    printf("    Group: %s\n", p->group);
}