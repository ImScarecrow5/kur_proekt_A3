#define _CRT_SECURE_NO_WARNINGS
#define N 10000
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

char field[N][N];

int coord1[N];
int coord2[N];
int sumcoords[N];

int cd3[N];
int cd[N];

char readField[N];

int correctField(int blackPoint, int x, int y)
{
    if (field[x][y] == '#') return 1;
    return 0;
}

int inArr(int arr1[N], int arr2[N], int a, int b, int blpoint)
{
    for (int i = 0; i < blpoint; ++i)
    {
        if (arr1[i] == a && arr2[i] == b) return 0;
    }
}

int inArr1(int arr1[N], int a, int b)
{
    for (int i = 0; i < b; ++i)
    {
        if (arr1[i] == a) return 0;
    }

    return 1;
}

int inArr2(int arr2[N], int a, int b)
{
    for (int i = 0; i < b; ++i)
    {
        if (arr2[i] == a) return 0;
    }

    return 1;
}

int findLastId()
{
    FILE* fp;

    struct information {
        char name[10];
        int id;
        char namelen[8];
        int length;
        char namewidth[7];
        int width;
    };
    struct information inf[N];

    fp = fopen("data.txt", "r");

    if (fp == NULL) return 1;

    int i = 0;

    while (fscanf(fp, "%s%d%s%d%s%d", &(inf[i].name), &(inf[i].id), &(inf[i].namelen), &(inf[i].length), &(inf[i].namewidth), &(inf[i].width)) != EOF)
    {
        fseek(fp, ((inf[i].length + 1) * (inf[i].width + 1) + 2), SEEK_CUR);
        ++i;
    }
    return i;
}

void roseWinds(int length, int width)
{
    srand(time(0));
    /*puts("Хотите самостоятельно ввести кол-во черных клеток?");*/
    char h[3];
    int blackPoint;
    /*if (scanf("%s", &h) == "да")
    {
        while (blackPoint < length * width - 1)
        {
            puts("введите кол-во черных клеток: ");
            scanf("%d", blackPoint);
            if (blackPoint >= length * width - 1) puts("Некорретные данные");
        }
    }
    else */blackPoint = rand() % (length * width - 1);
    int m = max(length, width);
    if (blackPoint < m) blackPoint = m;
    // заполнение поле "белыми клетками"
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            field[i][j] = '*';
        }
    }

    for (int i = 0; i < m; ++i)
    {
        coord1[i] = -1;
        coord2[i] = -1;
    }

    int c1, c2;

    int flag = 0;
    
    int rd = 0;
    int e;

    //printf("%d %d \n", m, rd);

    if (rd)
    {
        e = length;
        if (width == 1)
        {
            e = width;
            c1 = rand() % length; // строки
            c2 = rand() % width; // столбцы
            coord1[flag] = c1;
            coord2[flag] = c2;
            field[c1][c2] = '#';
            ++flag;
        }
        else
        {
            while (flag < length)
            {
                c1 = rand() % length; // строки
                c2 = rand() % width; // столбцы
                int a1 = inArr1(coord1, c1, length);
                if (a1)
                {
                    coord1[flag] = c1;
                    coord2[flag] = c2;
                    field[c1][c2] = '#';
                    ++flag;
                }
            }
        }
    }
    else
    {
        e = width;
        if (length == 1)
        {
            e = length;
            c1 = rand() % length; // строки
            c2 = rand() % width; // столбцы
            coord1[flag] = c1;
            coord2[flag] = c2;
            field[c1][c2] = '#';
            ++flag;
        }
        else
        {
            while (flag < width)
            {
                c1 = rand() % length; // строки
                c2 = rand() % width; // столбцы
                int a2 = inArr2(coord2, c2, width);
                if (a2)
                {
                    coord1[flag] = c1;
                    coord2[flag] = c2;
                    field[c1][c2] = '#';
                    ++flag;
                }
            }
        }
    }
    

    // создание черных клеток
    for (int i = 0; i < blackPoint - e; ++i)
    {
        int flag = 0;
        while (flag == 0)
        {
            c1 = rand() % length; // строки
            c2 = rand() % width; // столбцы
            int a = inArr(coord1, coord2, c1, c2, blackPoint - e);
            if (a != 0)
            {
                coord1[i] = c1;
                coord2[i] = c2;
                flag = 1;
            }
        }

        field[coord1[i]][coord2[i]] = '#';
    }


    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }

    puts("Записать поле в файл? (Введите 1)");
    puts("Иначе введите 0");
    int a;
    scanf("%d", &a);
    if (a == 1)
    {
        FILE* fp;
        fp = fopen("data.txt", "a");

        int id = findLastId();

        fprintf(fp, "Field: %d Length: %d Width: %d\n", ++id, length, width);

        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                fprintf(fp, "%c", field[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");

        fclose(fp);
    }
}

void showField(int key)
{
    FILE* fp;

    struct information {
        char name[10];
        int id;
        char namelen[8];
        int length;
        char namewidth[7];
        int width;
    };
    struct information inf[N];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("В файле нечего читать\n");
        return;
    }

    int i = 0;
    int flag = 0;
    while (fscanf(fp, "%s%d%s%d%s%d", &(inf[i].name), &(inf[i].id), &(inf[i].namelen), &(inf[i].length), &(inf[i].namewidth), &(inf[i].width)) != EOF)
    {
        if ((inf[i].length) < 1) continue;
        int pos = (inf[i].length) * (inf[i].width + 1);
        fseek(fp, pos, SEEK_CUR);
        ++i;
        if (key == i)
        {
            flag = 1;
            break;
        }
    }

    --i;

    if (!flag)
    {
        puts("В файле нет поля с таким ключом");
        return;
    }

    int pos = (inf[i].length + 1) * (inf[i].width + 1) + 1;
    fseek(fp, -pos, SEEK_CUR);

    char arrf[N];
    while (fgets(arrf, inf[i].width, fp) != NULL)
    {
        if (arrf[0] == ' ') return;
        if (arrf[0] != '*' && arrf[0] != '#') continue;
        printf("%s", arrf);
    }
}

void lastField()
{
    FILE* fp;

    struct information {
        char name[10];
        int id;
        char namelen[8];
        int length;
        char namewidth[7];
        int width;
    };
    struct information inf[N];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("В файле нечего читать\n");
        return;
    }

    int i = 0;
    int d = 0;
    while (fscanf(fp, "%s%d%s%d%s%d", &(inf[i].name), &(inf[i].id), &(inf[i].namelen), &(inf[i].length), &(inf[i].namewidth), &(inf[i].width)) != EOF)
    {
        if ((inf[i].length) < 1) continue;
        int pos = (inf[i].length) * (inf[i].width + 1);
        // d = pos - ((inf[i].length) * (inf[i].width));
        fseek(fp, pos, SEEK_CUR);
        ++i;
    }
    --i;
    int pos = (inf[i].length + 1) * (inf[i].width + 1) + 1;
    fseek(fp, -pos, SEEK_CUR);

    char arrf[N];
    while (fgets(arrf, inf[i].width, fp) != NULL)
    {
        if (arrf[0] != '*' && arrf[0] != '#') continue;
        printf("%s", arrf);
    }
}

void question()
{
    puts("Завершить выполнение программы? (Введите 0)");
    puts("Создать новое поле? (Введите 1)");
    puts("Вывести последнее поле из файла? (Введите 2)");
    puts("Вывести определенное поле по ключу (Введите 3)");
}

int main(void)
{
    setlocale(LC_ALL, "RUS");
    int d = -1;
    int flag = 1;
    while (flag)
    {
        question();
        unsigned ans;
        scanf("%d", &ans);

        switch (ans)
        {
        case 1:
            puts("Введите длину поля: ");
            int length;
            scanf("%d", &length);

            puts("Введите ширину поля: ");
            int width;
            scanf("%d", &width);
            roseWinds(length, width);
            break;
        case 0:
            flag = 0;
            break;
        case 2:
            lastField();
            break;
        case 3:
            puts("Введите id: ");
            int key;
            scanf("%d", &key);
            showField(key);
        }
    }
}
