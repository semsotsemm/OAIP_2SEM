#include <iostream>

using namespace std;

int main()
{
    int k, err, size = 0;
    FILE* ff, * fg;
    char simb;
    setlocale(LC_CTYPE, "Russian");
    err = fopen_s(&ff, "filef.txt", "r");
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    fseek(ff, 0L, SEEK_END);
    int fsize = ftell(ff);
    fseek(ff, 0L, SEEK_SET);
    for (int i = 0; i < fsize; i++)
    {
        fread((void*)&simb, sizeof(char), 1, ff);
        if (simb == ' ')
        {
            size++; //считаем количество чисел в файле
        }
    }
    fseek(ff, 0L, SEEK_SET);
    int* mass = new int[size];
    cout << "Считанные числа с файла f: \t";
    for (int i = 0; i < size; i++)
    {
        fscanf_s(ff, "%d", &mass[i]);
    }
    for (int i = 0; i < size; i++)
    {
        cout << mass[i] << '\t';
    }
    cout << "\nВведите число k: ";
    cin >> k;
    err = fopen_s(&fg, "fileg.txt", "w");
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    cout << "Записанные числа в файл g: \t";
    for (int i = 0; i < size; i++)
    {
        if (mass[i] % k == 0)
        {
            fprintf(fg, "%d ", mass[i]);
            cout << mass[i] << "\t";
        }
    }
}