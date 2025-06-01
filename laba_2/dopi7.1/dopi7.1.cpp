#include <iostream>

using namespace std;

int* creatematrix(int err, FILE* filei, int& colichnum)
{
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    fseek(filei, 0L, SEEK_SET);
    int* name = new int[colichnum];
    for (int i = 0; i < colichnum; i++)
    {
        fscanf_s(filei, "%d", &name[i]);
    }
    cout << "\nСчитанные данные:";
    for (int i = 0; i < colichnum; i++)
    {
        cout << name[i] << "\t";
    }
    fclose(filei);
    return name;
}
int main()
{
    setlocale(LC_CTYPE, "Russian");
    FILE* fnameA, * fnameB, * fnameC, * fnameD;
    int err = 0, colichnum = 0;
    char simb;
    fopen_s(&fnameA, "nameA.txt", "r");
    fseek(fnameA, 0L, SEEK_END);
    int fsize = ftell(fnameA); //считаем всю длинну строки
    fseek(fnameA, 0L, SEEK_SET);
    for (int i = 0; i < fsize; i++)
    {
        fread((void*)&simb, sizeof(char), 1, fnameA);
        if (simb == ' ')
        {
            colichnum++; //считаем сколько строк в матрице A
        }
    }
    int* A = creatematrix(err, fnameA, colichnum);
    fopen_s(&fnameB, "nameB.txt", "r");
    int* B = creatematrix(err, fnameA, colichnum);
    fopen_s(&fnameC, "nameC.txt", "r");
    int* C = creatematrix(err, fnameA, colichnum);
    fopen_s(&fnameD, "nameD.txt", "w");
    int* D = new int[colichnum];
    cout << "\nЗаписанные данные: ";
    for (int i = 0; i < colichnum; i++)
    {
        if (max(A[i], B[i]) == A[i])
        {
            D[i] = max(A[i], C[i]);
        }
        else
        {
            D[i] = max(B[i], C[i]);
        }
        cout << D[i] << "\t";
        fprintf(fnameD, "%d ", D[i]);
    }
}