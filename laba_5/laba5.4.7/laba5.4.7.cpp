#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

FILE* fnewdata;
FILE* fdata;

struct dateReceipt
{
    unsigned int day : 5;
    unsigned int mouth : 4;
    unsigned int year : 11;
};

enum bonusPercentage
{
    five = 5,
    seven = 7,
    ten = 10,
    twenty = 20,
    thirtyFive = 35
};

struct warehouse
{
    int id;
    char title[100];
    int price;
    int quantity;
    bonusPercentage premium;
    dateReceipt date;
};

int getId();

void printOriginWarehouse(int i);

void printTab(int num);

void printLine();

void outputWarehouse();

void inputWarehouse();

void deleteWarehouse();

void searchWarehouse();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int userInput;
    setlocale(LC_CTYPE, "Russian");
    cout << "Меню:\n" << "1 - Ввод данных о новом товаре, поступившем на склад\n" << "2 - Вывод информации о товарах на складе\n";
    cout << "3 - Удаление товара\n" << "4 - Поиск товара по цене\n" << "0 - Выход из программы\n";
    do
    {
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            inputWarehouse();
            break;
        case 2:
            outputWarehouse();
            break;
        case 3:
            deleteWarehouse();
            break;
        case 4:
            searchWarehouse();
            break;
        case 0:
            break;
        default:
            cout << "Ошибка выбора\n";
            break;
        }
        cout << "Что дальше? \n";
    } while (userInput != 0);
}

void printOriginWarehouse(int i)
{
    switch (i)
    {
    case 1:
        cout << "5%\n";
        break;
    case 2:
        cout << "7%\n";
        break;
    case 3:
        cout << "10%\n";
        break;
    case 4:
        cout << "20%\n";
        break;
    case 5:
        cout << "35%\n";
        break;
    default:
        break;
    }
}

int getId()
{
    warehouse buf;
    int newid = 0;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            if (newid < buf.id)
            {
                newid = buf.id;
            }
        }
        fclose(fdata);
    }
    else // файл не получилось открыть для чтения, значит его не сущестует, сотрудников нет newid=1;
    {
        newid = 0;
    }
    return newid + 1;
}

void printTab(int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << "\t";
    }
}

void printLine()
{
    cout << "________________________________________________________________\n";
}

void outputWarehouse()
{
    warehouse buf;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            printLine();
            cout << "Id: " << buf.id << "\n";
            cout << "Наименование товара: " << buf.title << "\n";
            cout << "Цена: " << buf.price << "\n";
            cout << "Количество товара: " << buf.quantity << "\n";
            cout << "Процент торговой надбавки: " << buf.premium << "%\n";
            cout << "Дата поступления на склад: " << buf.date.day << "." << buf.date.mouth << "." << buf.date.year << "\n";
        }
        fclose(fdata);
        printLine();
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void inputWarehouse()
{
    int size;
    warehouse buf;
    cout << "Введите сколько новых товаров хотите записать: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        buf.id = getId();
        fopen_s(&fdata, "data.bin", "ab");
        cin.ignore();
        cout << "Наименование товара: ";
        cin.getline(buf.title, 100);
        cout << "Введите цену: ";
        cin >> buf.price;
        cout << "Введите колчичество товара: ";
        cin >> buf.quantity;
        cout << "Введите процент торговой надбавки:\n";
        int percent;
        for (int i = 1; i < 6; i++)
        {
            cout << i << " - ";
            printOriginWarehouse(i);
        }
        cin >> percent;
        switch (percent)
        {
        case 1:
            buf.premium = five;
            break;
        case 2:
            buf.premium = seven;
            break;
        case 3:
            buf.premium = ten;
            break;
        case 4:
            buf.premium = twenty;
            break;
        case 5:
            buf.premium = thirtyFive;
            break;
        default:
            break;
        }
        int date;
        cout << "Введите год выпуска книги: ";
        cin >> date;
        buf.date.year = date;
        cout << "Введите месяц выпуска книги: ";
        cin >> date;
        buf.date.mouth = date;
        cout << "Введите день выпуска книги: ";
        cin >> date;
        buf.date.day = date;
        fwrite(&buf, sizeof(buf), 1, fdata);
        fclose(fdata);
    }
}

void deleteWarehouse()
{
    warehouse buf;
    int index;
    cout << "Введите id товара которого хотите удалить: ";
    cin >> index;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        fopen_s(&fnewdata, "newdata.bin", "wb");
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            if (index == buf.id)
            {
                continue;
            }
            fwrite(&buf, sizeof(buf), 1, fnewdata);
        }
        fclose(fnewdata);
        fclose(fdata);
        remove("data.bin");
        rename("newdata.bin", "data.bin");
        cout << "Товар успешно удален из списка\n";
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void searchWarehouse()
{
    warehouse buf;
    int price;
    cout << "Введите цену по которой хотите найти товар: ";
    cin >> price;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            if (buf.price == price)
            {
                printLine();
                cout << "Наименование товара: " << buf.title << "\n";
                cout << "Цена" << buf.price << "\n";
                cout << "Количество товара: " << buf.quantity << "\n";
                cout << "Процент торговой надбавки: " << buf.premium <<"%\n";
                cout << "Дата поступления на склад: " << buf.date.day << "."<<buf.date.mouth << "." << buf.date.year << "\n";
                printLine();
            }
        }
    }
}