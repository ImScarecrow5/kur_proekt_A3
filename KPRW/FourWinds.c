#define _CRT_SECURE_NO_WARNINGS
#define N 10000
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


char field[N][N];

int coord1[N];
int coord2[N];
int sumcoords[N];

int inArr(int arr1[N], int arr2[N], int a, int b, int blpoint)
{
    for (int i = 0; i < blpoint; ++i)
    {
        if (arr1[i] == a && arr2[i] == b) return 0;
    }

    return 1;
}

int main(void)
{
    setlocale(LC_ALL, "");

    puts("Введите длину поля: ");
    int length;
    scanf("%d", &length);

    puts("Введите длину поля: ");
    int width;
    scanf("%d", &width);

    srand(time(0));
    int blackPoint = rand() % (length * width);
    //printf("%d\n", blackPoint);

    // заполнение поле "белыми клетками"
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            field[i][j] = '*';
        }
    }

    int c1, c2;
    // создание черных клеток
    for (int i = 0; i < blackPoint; ++i)
    {
        int flag = 0;
        while (flag == 0)
        {
            c1 = rand() % length; // строки
            c2 = rand() % width; // столбцы
            int a = inArr(coord1, coord2, c1, c2, blackPoint);
            if (a != 0)
            {
                coord1[i] = c1;
                coord2[i] = c2;
                flag = 1;
            }
        }

        field[coord1[i]][coord2[i]] = '#';
    }

    // отрисовка игрового поля без линий
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    //for (int i = 0; i < blackPoint; ++i)
    //{
    //    printf("%d %d\n", coord1[i], coord2[i]);
    //}

    // сортировка координат
    for (int i = 0; i + 1 < blackPoint; ++i)
    {
        for (int j = 0; j + 1 < blackPoint - i; ++j)
        {
            if (coord1[j + 1] < coord1[j])
            {
                int t = coord1[j];
                coord1[j] = coord1[j + 1];
                coord1[j + 1] = t;
                t = coord2[j];
                coord2[j] = coord2[j + 1];
                coord2[j + 1] = t;
            }
        }
    }

    //for (int i = 0; i < blackPoint; ++i)
    //{
    //    printf("%d %d\n", coord1[i], coord2[i]);
    //}

    // создание линий coord1 - строки, coord2 - столбцы
    for (int point = 0; point < blackPoint; ++point)
    {
        int whiteCells = 0;
        int coordstart = 0;
        int l = coord1[point];
        int w = coord2[point];
        for (int i = 0; i < coord2[point]; ++i) {
            if (coordstart >= coord2[point]) break;
            else if (field[l][i] == '#' || field[l][i] == '-' || field[l][i] == '|')
            {
                coordstart = i + 1;
                whiteCells = 0;
                continue;
            }
            else if (field[l][i] == '*')
            {
                ++whiteCells;
            }
        }

        if (whiteCells != 0)
        {
            // отрисовка горизонтальных линий слева
            for (int i = coordstart; i < coord2[point]; ++i)
            {
                field[l][i] = '-';
            }
        }

        sumcoords[point] += whiteCells;
        whiteCells = 0;

        coordstart = coord2[point];

        for (int i = coord2[point] + 1; i < width; ++i) 
        {
            if (field[l][i] == '#' || field[l][i] == '-' || field[l][i] == '|')
            {
                break;
            }
            else if (field[l][i] == '*')
            {
                ++coordstart;
                ++whiteCells;
            }
        }

        if (whiteCells != 0)
        {
            // отрисовка горизонтальных линий справа
            for (int i = coord2[point] + 1; i < coordstart + 1; ++i)
            {
                field[l][i] = '-';
            }
        }

        sumcoords[point] += whiteCells;
        whiteCells = 0;


        coordstart = 0;

        for (int i = 0; i < coord1[point]; ++i)
        {
            if (coordstart >= coord1[point]) break;
            else if (field[i][w] == '#' || field[i][w] == '-' || field[i][w] == '|')
            {
                coordstart = i + 1;
                whiteCells = 0;
                continue;
            }
            else if (field[i][w] == '*')
            {
                ++whiteCells;
            }
        }

        if (whiteCells != 0)
        {
            // отрисовка вертикальных линий сверху
            for (int i = coordstart; i < coord1[point]; ++i)
            {
                field[i][w] = '|';
            }
        }

        sumcoords[point] += whiteCells;
        whiteCells = 0;
        coordstart = coord1[point] + 1;

        for (int i = coord1[point] + 1; i < length; ++i)
        {
            if (field[i][w] == '#' || field[i][w] == '-' || field[i][w] == '|')
            {
                break;
            }
            else if (field[i][w] == '*')
            {
                ++coordstart;
                ++whiteCells;
            }
        }

        if (whiteCells != 0)
        {
            // отрисовка вертикальных линий снизу
            for (int i = coord1[point] + 1; i < coordstart + 1; ++i)
            {
                field[i][w] = '|';
            }
        }
        sumcoords[point] += whiteCells;
    }

    // добавление к черному квадрату его кол-во линий
    for (int point = 0; point < blackPoint; ++point) field[coord1[point]][coord2[point]] = sumcoords[point] + '0';

    // отрисовка рамка ч.1
    printf(" _");
    for (int i = 0; i < width; ++i) printf("_");
    printf("_\n| ");
    for (int i = 0; i < width; ++i) printf(" ");
    printf(" |\n");

    // отрисовка результата (поле)
    for (int i = 0; i < length; ++i)
    {
        printf("| ");
        for (int j = 0; j < width; ++j)
        {
            printf("%c", field[i][j]);
        }
        /*if (i == length - 1)
        {
            printf(" |");
            break;
        }*/
        printf(" |\n");
    }


    // отрисовка рамки ч.2
    printf("|_");
    for (int i = 0; i < width; ++i) printf("_");
    printf("_|");
}
