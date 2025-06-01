#include <iostream>

using namespace std;

float* creatematrix(int err, FILE* filei, int& size)
{
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return 0;
    }
    char simb;
    int fsize;
    fseek(filei, 0L, SEEK_END);
    fsize = ftell(filei); //считаем всю длинну строки
    fseek(filei, 0L, SEEK_SET);
    for (int i = 0; i < fsize; i++)
    {
        fread((void*)&simb, sizeof(char), 1, filei);
        if (simb == ' ')
        {
            size++; //считаем сколько чилел в строке
        }
    }
    fseek(filei, 0L, SEEK_SET);
    float* A = new float[size];
    for (int i = 0; i < size; i++)
    {
        fscanf_s(filei, "%f", &A[i]); //заполняем массив числами, считанными  с файла
    }
    cout << "Считанные числа:\n";
    for (int i = 0; i < size; i++)
    {
        cout << A[i] << "\t";
    }
    fclose(filei);
    return A;
}
int main()
{
    setlocale(LC_CTYPE, "Russian");
    FILE* fA;
    int size = 1, err;
    float minraznica, el, num,index;
    err = fopen_s(&fA, "A.txt", "r"); // функция возвращает 0 если удалось открыть файл
    float* A = creatematrix(err, fA, size);
    cout << "\nВведите ваше число: ";
    cin >> num;
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            minraznica = num - A[i];
        }
        if (abs(num - A[i]) < abs(minraznica)) //ищем число, наиболее близкое к введенному
        {
            minraznica = num - A[i];
            el = A[i];
            index = i + 1;
        }
    }
    cout << "Число: "<<el<<", его порядковый номер: "<<index;
    delete A;
}