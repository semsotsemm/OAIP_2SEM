#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

FILE* fnewdata;
FILE* fdata;

struct dateOfWriting
{
    unsigned int day : 5;
    unsigned int mouth : 4;
    unsigned int year : 11;
};

enum originOfTheBook
{
    purchase = 1,
    steal = 2,
    present = 3

};

struct Book
{
    int id;
    char author[100];
    char title[100];
    char publishing[100];
    int chapters;
    originOfTheBook origin;
    bool availability;
    dateOfWriting date;
};

int getId();

void printOriginBook(int i);

void printTab(int num);

void printline();

void outputBook();

void inputBook();

void deleteBook();

void searchBook();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int userInput;
    setlocale(LC_CTYPE, "Russian");
    cout << "Меню:\n" << "1 - Ввод данных о новой книге\n" << "2 - Вывод информации о библиотеке\n";
    cout << "3 - Удаление книги\n" << "4 - Поиск книгу по году\n" << "0 - Выход из программы\n";
    do
    {
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            inputBook();
            break;
        case 2:
            outputBook();
            break;
        case 3:
            deleteBook();
            break;
        case 4:
            searchBook();
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

void printOriginBook(int i)
{
    if (i == 1)
    {
        cout << "Покупка\n";
    }
    else if (i == 2)
    {
        cout << "Кража\n";
    }
    else
    {
        cout << "Подарок\n";
    }
}

int getId()
{
    Book buf;
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

void printline()
{
    cout << "________________________________________________________________\n";
}

void outputBook()
{
    Book buf;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            printline();
            cout << "Id: " << buf.id << "\n";
            cout << "Название книги: " << buf.title << "\n";
            cout << "Автор: " << buf.author << "\n";
            cout << "Публикация: " << buf.publishing << "\n";
            cout << "Количество глав: " << buf.chapters << "\n";
            cout << "Есть ли книга в наличии: ";
            buf.availability ? cout << "Есть" : cout << "Нет";
            cout << "Происхождение: ";
            printOriginBook(buf.origin);
            cout << "\nДата публикации: " << buf.date.day << "." << buf.date.mouth << "." << buf.date.year << "\n";
        }
        fclose(fdata);
        printline();
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void inputBook()
{
    int size;
    Book buf;
    cout << "Введите сколько новых книг хотите записать: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        buf.id = getId();
        fopen_s(&fdata, "data.bin", "ab");
        cin.ignore();
        cout << "Введите автора книги: ";
        cin.getline(buf.author, 100);
        cout << "Введите издание книги: ";
        cin.getline(buf.publishing, 100);
        cout << "Введите название книги: ";
        cin.getline(buf.title, 100);
        cout << "Введите количество глав: ";
        cin >> buf.chapters;
        cout << "Введите происхождение книги:\n";
        for (int i = 1; i < 4; i++)
        {
            cout << i <<" - ";
            printOriginBook(i);
        }
        int origin;
        cin >> origin;
        switch (origin)
        {
        case 1:
            buf.origin = purchase;
            break;
        case 2:
            buf.origin = steal;
            break;
        case 3:
            buf.origin = present;
            break;
        default:
            break;
        }
        cout << "Введите есть ли книга в наличии (1 - Да, 0 - Нет): ";
        cin >> buf.availability;
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

void deleteBook()
{
    Book buf;
    int index;
    cout << "Введите id ученика которого хотите удалить: ";
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
        cout << "Ученик успешно удален из списка\n";
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void searchBook()
{
    Book buf;
    int year;
    cout << "Введите год происхождения книги: ";
    cin >> year;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            if (buf.date.year == year)
            {
                printline();
                cout << "Id: " << buf.id << "\n";
                cout << "Название книги: " << buf.title << "\n";
                cout << "Автор: " << buf.author << "\n";
                cout << "Публикация: " << buf.publishing << "\n";
                cout << "Количество глав: " << buf.chapters;
                cout << "Есть ли книга в наличии: ";
                buf.availability ? cout << "Есть" : cout <<"Нет";
                cout << "Происхождение: ";
                switch (buf.origin)
                {
                case 1:
                    cout << "Покупка\n";
                    break;
                case 2:
                    cout << "Кража\n";
                    break;
                case 3:
                    cout << "Подарок\n";
                    break;
                default:
                    break;
                }
                cout << "Дата публикации: " << buf.date.day <<"."<< buf.date.mouth << "." << buf.date.year << "\n";
                printline();
            }
        }
    }
}