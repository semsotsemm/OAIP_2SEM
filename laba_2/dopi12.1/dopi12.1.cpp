#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_CTYPE, "Russian");
    FILE* fA, * fB;
    int colsA, rowsA, err, k;
    err = fopen_s(&fA, "A.txt", "r"); // функция возвращает 0 если удалось открыть файл
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    fscanf_s(fA, "%d", &colsA); // определяем 1 число из файла как количество колонок матрицы A
    char simb;
    int fsize, colichnum = 0;
    fseek(fA, 0L, SEEK_END);
    fsize = ftell(fA); //считаем всю длинну строки
    fseek(fA, 0L, SEEK_SET);
    for (int i = 0; i < fsize; i++)
    {
        fread((void*)&simb, sizeof(char), 1, fA);
        if (simb == ' ')
        {
            colichnum++; //считаем сколько строк в матрице A
        }
    }
    rowsA = colichnum / colsA;
    fseek(fA, 2L, SEEK_SET); //устанавливаем курсос в 2 позицию от начала
    float** A = new float* [rowsA];
    for (int i = 0; i < rowsA; i++)
    {
        A[i] = new float[colsA]; // создаем матрицу A
    }
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            fscanf_s(fA, "%f", &A[i][j]);
        }
    }
    cout << "Матрица А:\n";
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << "Введите номер строки которую хотите записать в файл B:";
    cin >> k;
    err = fopen_s(&fB, "B.txt", "w"); // функция возвращает 0 если удалось открыть файл
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            if (i + 1 == k)
            {
                fprintf(fB, "%3.1f ", A[i][j]);
            }
        }
    }
    cout << "Числа успешно записаны!";
    fclose(fA);
    for (int i = 0; i < rowsA; i++)
        delete A[i];
    delete A;
}