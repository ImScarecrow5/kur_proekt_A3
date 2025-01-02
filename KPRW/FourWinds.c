#define _CRT_SECURE_NO_WARNINGS
#define N 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

struct information {
    char name[10];
    int id;
    char namelen[8];
    int length;
    char namewidth[7];
    int width;
};

void check(int rd, char field[N][N], int coord1[N], int coord2[N], int length, int width, int blackPoint);
void changeName(char* filename);
int findLastId(char* filename);
void writeToAFile(char* filename, int length, int width, char field[N][N]);
void writeOrNot(char* filename, int length, int width, char field[N][N]);
void roseWinds(char* filename, int length, int width);
void showField(char* filename, int key);
void lastField(char* filename);
void question();

int main(void)
{
    setlocale(LC_ALL, "RUS");

    puts("Данная программа предначена для генерации полей для игра \"Роза ветров\" (Rose winds)");
    puts("Все созданные поля будут записаны по умолчанию в файл \"data.txt\" для дальнейшего использования полей в игре");

    char filename[50] = { 'd', 'a', 't', 'a', '.', 't', 'x', 't' };

    int flag = 1;

    while (flag)
    {
        question();

        printf("Текущее название файла: %s, количество полей в файле: %d\n", filename, findLastId(&filename));

        unsigned answer;
        scanf("%d", &answer);

        switch (answer)
        {
        case 1:
            puts("Введите длину поля (макс. 100): ");
            int length;
            scanf("%d", &length);

            puts("Введите ширину поля (макс. 100): ");
            int width;
            scanf("%d", &width);

            if (length > 100 || width > 100)
            {
                puts("Неверные данные");
                break;
            }

            roseWinds(&filename, length, width);
            break;
        case 0:
            flag = 0;
            break;
        case 2:
            lastField(&filename);
            break;
        case 3:
            puts("Введите id: ");
            int key;
            scanf("%d", &key);

            showField(filename, key);
            break;
        case 4:
            changeName(&filename);

            break;
        default:
            puts("Введите корректную цифру");
            break;
        }
    }
}

/*
-ищет в файле последний ключ
-filename - имя файла
-возвращает ключ
*/
int findLastId(char* filename)
{
    FILE* fp;

    struct information inf[N];

    int i = 0;

    fp = fopen(filename, "r");

    if (fp == NULL) return 0;

    while (fscanf(fp, "%s%d%s%d%s%d", &(inf[i].name), &(inf[i].id), &(inf[i].namelen), &(inf[i].length), &(inf[i].namewidth), &(inf[i].width)) != EOF)
    {
        fseek(fp, ((inf[i].length + 1) * (inf[i].width + 1) + 2), SEEK_CUR);
        ++i;
    }
    return i;
}


/*
-записывает поле в файл
-filename - имя файла, length - длина поля, width - ширина поля, field[N][N] - игровое поле
-ничего не возвращает
*/
void writeToAFile(char* filename, int length, int width, char field[N][N])
{
    int id = findLastId(filename);

    FILE* fp;

    fp = fopen(filename, "a");

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

    puts("Запись в файл прошла успешно");

    fclose(fp);
}

/*
-Спрашивает у пользователя, необходимо ли записать поле в файл
-filename - имя файла, length - длина поля, width - ширина поля, field[N][N] - игровое поле
-ничего не возвращает
*/
void writeOrNot(char* filename, int length, int width, char field[N][N])
{
    unsigned answer;

    puts("Записать поле в файл? (Введите 1)");
    puts("Иначе введите любую иную цифру для продолжения");

    scanf("%d", &answer);
    if (answer == 1) writeToAFile(filename, length, width, field);
}

/*
-Меняет название файла, который используется для записи и чтения
-filename - имя файла
-ничего не возвращает
*/
void changeName(char* filename)
{
    puts("Введите названия файла: ");

    char filename2[50];
    scanf("%s", &filename2);

    char rs[5] = { '.', 't', 'x', 't' };

    char* txt = strstr(filename2, rs);
    if (!txt)
    {
        strcat(filename2, rs);
    }

    strcpy(filename, filename2);

    puts("Новый файл сохранен по умолчанию");

}

/*
-создает игровое поле
-filename - имя файла, length - длина поля, width - ширина поля
-ничего не возвращает
*/
void roseWinds(char* filename, int length, int width)
{
    int coord1[N];
    int coord2[N];

    char field[N][N];

    int blackPoint;

    int max = max(length, width);
    int min = min(length, width);

    srand(time(NULL));
    blackPoint = rand() % (length * width - 1);

    int rd = rand() % 2;
    int len;
    if (blackPoint < max && min != 1) blackPoint = max;

    // заполнение всего поля "белыми клетками"
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            field[i][j] = '*';
        }
    }

    for (int i = 0; i < max; ++i)
    {
        coord1[i] = -1;
        coord2[i] = -1;
    }

    int c1, c2;

    int flag = 0;

    // генерация координат черных клеток
    if (rd)
    {
        len = length;
        if (width == 1)
        {
            len = width;
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
                int a1 = 1;
                for (int i = 0; i < length; ++i)
                {
                    if (coord1[i] == c1)
                    {
                        a1 = 0;
                        break;
                    }
                }
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
        len = width;
        if (length == 1)
        {
            len = length;
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
                int a2 = 1;
                for (int i = 0; i < width; ++i)
                {
                    if (coord2[i] == c2)
                    {
                        a2 = 0;
                        break;
                    }
                }
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


    // создание дополнительных черных клеток
    for (int i = len + 1; i < blackPoint; ++i)
    {
        int flag = 0;
        while (flag == 0)
        {
            c1 = rand() % length; // строки
            c2 = rand() % width; // столбцы
            int a = 1;

            for (int i = 0; i < blackPoint; ++i)
            {
                if (coord1[i] == c1 && coord2[i] == c2)
                {
                    a = 0;
                    break;
                }
            }

            if (a)
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

    check(rd, field, coord1, coord2, length, width, len);

    writeOrNot(filename, length, width, field);
}


/*
-проверяет созданное поле на правильность
-rd - способ создания поля, field[N][N] - игровое поле, 
-coord1 - координаты черных клеток по Oy, coord2 - координаты черных клеток по Ox,
-length - длина поля, width - ширина поля, blackPoint - количество "главных" черных клеток.
-ничего не возвращает
*/
void check(int rd, char field[N][N], int coord1[N], int coord2[N], int length, int width, int blackPoint)
{
    int count = 0;
    if (rd)
    {
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < blackPoint; ++j)
            {
                if (coord1[j] == i)
                {
                    ++count;
                    break;
                }
            }
            if (count == i) break;
        }
        if (count == length)
        {
            puts("Поле сгенерировалось верно");
        }
        else
        {
            puts("Поле сгенерировалось неверно");
        }
    }
    else
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < blackPoint; ++j)
            {
                if (coord2[j] == i)
                {
                    ++count;
                    break;
                }
            }
            if (count == i) break;
        }
        if (count == width)
        {
            puts("Поле сгенерировалось верно");
        }
        else
        {
            puts("Поле сгенерировалось неверно");
        }
    }
}

/*
-выводит необходимое поле
-filename - имя файла, key - ключ
-ничего не возвращает
*/
void showField(char* filename, int key)
{
    FILE* fp;

    struct information inf[N];

    fp = fopen(filename, "r");

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
        puts("В файле нет требуемого поля");
        return;
    }

    int pos = (inf[i].length + 1) * (inf[i].width + 1) + 1;
    fseek(fp, -pos, SEEK_CUR);

    char arrf[N];
    int width = inf[i].width;
    int length = inf[i].length;
    i = 0;
    while (i < length)
    {
        fgets(arrf, width + 2, fp);
        if (arrf[0] != '*' && arrf[0] != '#') continue;
        printf("%s", arrf);
        ++i;
    }
}

/*
-выводит последнее поле
-filename - имя файла
-ничего не возвращает
*/
void lastField(char* filename)
{
    int id = findLastId(filename);

    showField(filename, id);
}

/*
-выводит окно с вопросами
-ничего не принимает
-ничего не возвращает
*/
void question()
{
    puts("Завершить выполнение программы? (Введите 0)");
    puts("Создать новое поле? (Введите 1)");
    puts("Вывести последнее поле из файла? (Введите 2)");
    puts("Вывести определенное поле по ключу (Введите 3)");
    puts("Ввести новое имя файла (Введите 4)");
}
