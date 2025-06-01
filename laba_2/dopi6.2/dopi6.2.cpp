#include <iostream>

using namespace std;

int main()
{
    FILE* f1, * f2;
    int fsize, err, strok = 1;
    char simb;
    setlocale(LC_CTYPE, "Russian");
    err = fopen_s(&f2, "F2.txt", "r"); // функция возвращает 0 если удалось открыть файл
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    fseek(f2, 0L, SEEK_END);
    fsize = ftell(f2); //считаем всю длинну строки
    fseek(f2, 0L, SEEK_SET);
    err = fopen_s(&f1, "F1.txt", "w");
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    cout << "Записанные строки:\n";
    for (int i = 0; i < fsize; i++)
    {
        if (strok == 1)
        {
            fread((void*)&simb, sizeof(char), 1, f2);
        }
        if (simb == '\n')
        {
            strok++; 
            if (strok % 2 == 0) //Если строка четная записываем в F1 ее содержимое
            {
                fread((void*)&simb, sizeof(char), 1, f2);
                for (int j = 0; simb != '\n' && j != fsize; j++)
                {
                    cout << simb;
                    fprintf(f1, "%c", simb);
                    fread((void*)&simb, sizeof(char), 1, f2);
                }
                cout << endl;
                fprintf(f1, "%c", '\n');
            }
            else //Если строка нечетная ищет начало следующей строки
            {
                fread((void*)&simb, sizeof(char), 1, f2);
                for (int j = 0; simb != '\n' && j != fsize; j++)
                {
                    fread((void*)&simb, sizeof(char), 1, f2);
                }
            }
        }
    }
}