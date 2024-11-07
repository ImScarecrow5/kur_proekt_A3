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

int roseWinds(int length, int width)
{
    srand(time(0));
    int blackPoint = rand() % (length * width - 1);
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

    printf("%d %d \n", m, rd);

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
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                fprintf(fp, "%c", field[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, " \n");

        fclose(fp);
        return (length + 1) * (width + 1);
    }
    return -1;
}

void lastField(int pos)
{
    FILE* fp;
    fp = fopen("data.txt", "r");
    fseek(fp, -pos, SEEK_END);
    if (fp == NULL)
    {
        printf("В файле нечего читать\n");
        return;
    }

    int i = 0;
    fscanf(fp, "%c", &readField[i]);
    if (!readField[i])
    {
        printf("В файле нечего читать\n");
        return;
    }
    else printf("%c", readField[i]);
    ++i;

    while (fscanf(fp, "%c", &readField[i]) != NULL)
    {
        if (readField[i] == ' ') return;
        if (!readField[i])
        {
            return;
        }
        printf("%c", readField[i]);
        ++i;
    }
}

void question()
{
    puts("Завершить выполнение программы? (Введите 0)");
    puts("Создать новое поле? (Введите 1)");
    puts("Вывести последнее поле из файла? (Введите 2)");
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
            d = roseWinds(length, width);
            break;
        case 0:
            flag = 0;
            break;
        case 2:
            if (d != -1) lastField(d);
            else puts("Запишите хотя бы 1 поле за время выполнения программы");
            break;
        }
    }
}
