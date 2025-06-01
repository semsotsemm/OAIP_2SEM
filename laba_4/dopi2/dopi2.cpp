#include <iostream>
#include <windows.h>
#include <cstring>

using namespace std;

FILE* fdata;

typedef struct TRAIN {
    int index;                   // Номер поезда
    char pose[100];              // Пункт назначения
    char time[5];                // Время отправления
} TR;

TR* sorttrain(TR buf[], int size);

void input() {
    const int SIZE = 3;
    TR buf[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        buf[i].index = i + 1;
        cout << "Введите информацию о " << buf[i].index << " поезде:\n";
        cout << "Пункт назначения:\n";
        cin.ignore();
        cin.getline(buf[i].pose, 100);
        cout << "Время отправления:\n";
        cin >> buf[i].time;
    }
    fopen_s(&fdata, "data.bin", "ab");
    fwrite(buf, sizeof(TR), SIZE, fdata);  // Записываем каждый поезд по отдельности
    fclose(fdata);
    cout << "Информация успешно записана\n";
}

void showlist() {
    const int SIZE = 3;
    TR buf[SIZE];
    cout << "Пункт назначения: \t\t\t|\tВремя отправления\t|\tНомер поезда\t|\n";
    cout << "_________________________________________________________________________________________________\n";

    if (!fopen_s(&fdata, "data.bin", "rb")) {
        fread(buf, sizeof(TR), SIZE, fdata);  // Читаем все записи
        fclose(fdata);
    }
    else {
        cout << "Ошибка открытия файла для чтения\n";
        return;
    }

    TR* sortedBuf = sorttrain(buf, SIZE);  // Сортируем данные
    for (int i = 0; i < SIZE; i++) {
        cout << sortedBuf[i].pose << "\r\t\t\t\t\t|\t\t" << sortedBuf[i].time << "\t\t|\t\t" << sortedBuf[i].index << "\t|\n";
    }
}

TR* sorttrain(TR buf[], int size) {
    TR sort;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (strcmp(buf[i].pose, buf[j].pose) > 0) // Сравниваем строки (пункты назначения)
            {  
                sort = buf[i];
                buf[i] = buf[j];
                buf[j] = sort;
            } // Меняем местами все поля
        }
    }
    return buf;
}

bool checktime(char time[], TR buf)
{
    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;
        }
        if (buf.time[i] > time[i])
        {
            return 1;
        }
        else if (buf.time[i] < time[i])
        {
            return 0;
        }
    }
}

void searchtrain(char time[])
{
    int check=0, SIZE = 3;
    TR buf[3];
    if (!fopen_s(&fdata, "data.bin", "rb")) 
    {
        while (fread(buf, sizeof(TR), SIZE, fdata));
    }
    else
    {
        cout << "Не удалось открыть файл";
    }
    for (int i = 0; i < SIZE; i++)
    {
        if (checktime(time,buf[i]))
        {
            cout << buf[i].pose << "\t\t" << buf[i].time << "\t\t" << buf[i].index << endl;
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char time[5];
    int user_input;
    cout << "Выберите операцию:\n" << "1 - Ввод новой информации\n";
    cout << "2 - Вывод информации о всех поездах\n" << "3 - Поиск поезда\n";
    cout << "0 - Для выхода из программы\n";

    do {
        cin >> user_input;
        switch (user_input) {
        case 1:
            input();
            break;
        case 2:
            showlist();
            break;
        case 3:
            cout << "Введите время, после которого вы свободны\n";
            cin >> time;
            searchtrain(time);
            break;
        case 0:
            break;
        }
        cout << "Что дальше?\n";
    } while (user_input != 0);

    return 0;
}