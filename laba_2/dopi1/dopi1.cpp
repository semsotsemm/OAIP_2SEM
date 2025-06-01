#include <iostream>

using namespace std;

float** creatematrix(int err, FILE* filei, int& rows, int& cols)
{
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    fscanf_s(filei, "%d", &cols); // определяем 1 число из файла как количество колонок матрицы A
    char simb;
    int fsize, colichnum = 0;
    fseek(filei, 0L, SEEK_END);
    fsize = ftell(filei); //считаем всю длинну строки
    fseek(filei, 0L, SEEK_SET);
    for (int i = 0; i < fsize; i++)
    {
        fread((void*)&simb, sizeof(char), 1, filei);
        if (simb == ' ')
        {
            colichnum++; //считаем сколько строк в матрице A
        }
    }
    rows = colichnum / cols;
    fseek(filei, 2L, SEEK_SET); //устанавливаем курсос в 2 позицию от начала
    float** A = new float* [rows];
    for (int i = 0; i < rows; i++)
    {
        A[i] = new float[cols]; // создаем матрицу A
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf_s(filei, "%f", &A[i][j]);
        }
    }
    cout << "Матрица А:\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    fclose(filei);
    return A;
}
int main()
{
    setlocale(LC_CTYPE, "Russian");
    FILE* fA, * fB, * fC;
    int colsA, colsB, colsC, rowA, rowB, rowC, err;
    err = fopen_s(&fA, "A.txt", "r"); // функция возвращает 0 если удалось открыть файл
    float** A = creatematrix(err, fA, rowA, colsA);
    err = fopen_s(&fB, "B.txt", "r");
    float** B = creatematrix(err, fB, rowB, colsB);
    rowC = rowA;
    colsC = colsB;
    float** C = new float* [rowC];
    for (int i = 0; i < rowC; i++)
    {
        C[i] = new float[colsC];
    }
    for (int i = 0; i < rowC; i++)
    {
        for (int j = 0; j < colsC; j++)
        {
            C[i][j] = 0;
        }
    }
    if (rowA == colsB && rowB == colsA)
    {
        err = fopen_s(&fC, "C.txt", "w");
        if (err != 0)
        {
            perror("Невозможно создать файл\n");
            return 0;
        }
        fprintf(fC, "%d ", colsC);
        for (int i = 0; i < rowC; i++)
        {
            for (int j = 0; j < colsC; j++)
            {
                for (int k = 0; k < rowB; k++)
                {
                    *(*(C + i) + j) += *(*(A + i) + k) * *(*(B + k) + j);
                }
            }
        }
        cout << "Произведение матриц:\n";
        for (int i = 0; i < rowC; i++)
        {
            for (int j = 0; j < colsC; j++)
            {
                cout << C[i][j] << '\t';
                fprintf(fC, "%3.2f ", C[i][j]);
            }
            cout << endl;
        }
    }
    else
        cout << "Матрицы нельзя умножить";
    for (int i = 0; i < rowA; i++)
        delete A[i];
    for (int i = 0; i < rowB; i++)
        delete B[i];
    for (int i = 0; i < rowC; i++)
        delete C[i];
    delete A;
    delete B;
    delete C;
}