#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    char s[1000];
    int a;
    errno_t err; // переменная err для хранения кода ошибки
    FILE* f; //создаем указатель для работы с файлом
    err = fopen_s(&f, "test.txt", "w"); // если файл получится открыть для изменения fopen_s вернет 0 
    if (err != 0)
    {
        perror("Невозможно создать файл\n");
        return EXIT_FAILURE; // возвращает код ошибки
    }
    for (a = 3; a < 100; a += 3)
    {
        fprintf(f, "%d, ", a); // заполняем файл числами, кратными 3
    }
    printf("Данные записаны в файл test.txt\n");
    fclose(f);

    err = fopen_s(&f, "test.txt", "r"); // если файл получится открыть для изменения fopen_s вернет 0 
    if (err != 0)
    {
        perror("Невозможно открыть файл для чтения\n");
        return EXIT_FAILURE; // возвращает код ошибки
    }    
    fgets(s, sizeof(s), f);
    fclose(f);
    cout << s;
    return 0;
}
