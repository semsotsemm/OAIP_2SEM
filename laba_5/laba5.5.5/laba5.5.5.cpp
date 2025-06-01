#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

union Аuthor
{
    char fullFio[40];
    char shortFio[40];
};

struct Library
{
    Аuthor authorFio;
    string title;
    string publishing;
    string chapter;
    string origin;
    bool availability;
    Library* next;

    Library()
    {
        next = nullptr;
    }
};

void printLine();

void printMenu();

bool convertToInt(string line, int& userInput);

bool pushNewLibrary(Library*& firstLibrary, Library* newLibrary);

void printLibrarys(Library* firstLibrary);

void pushLibrarysIntoFile(Library* firstLibrary, fstream& fdata);

void getInfoFromFile(Library*& firstLibrary, fstream& fdata);

bool popLibrary(Library*& firstLibrary);

bool cleanList(Library*& firstLibrary);

void getShortName(Library*& ptr);

bool cleanFile();

Library* searchLibrary(Library* firstLibrary, char fio[]);

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string line;
    int userInput;
    fstream fdata;
    Library* firstLibrary = nullptr;
    printMenu();
    while (true)
    {
        cin >> line;
        if (convertToInt(line, userInput))
        {
            switch (userInput)
            {
            case 1:
            {
                Library* newLibrary = new Library;
                cout << "Введите информацию о новой книге:\n";
                cout << "Введите фио автора книги: ";
                cin.ignore();
                cin.getline(newLibrary->authorFio.fullFio, 40);
                cout << "Введите название книги: ";
                getline(cin, newLibrary->title);
                cout << "Введите дату публикации (в формате дд.мм.гггг): ";
                getline(cin, newLibrary->publishing);
                cout << "Введите раздел библиотеки: ";
                getline(cin, newLibrary->chapter);
                cout << "Введите происхождение (покупка, кража, подарок, ...): ";
                getline(cin, newLibrary->origin);
                cout << "Введите наличие книги (0 - нет, 1 - есть): ";
                cin >> newLibrary->availability;
                if (pushNewLibrary(firstLibrary, newLibrary))
                {
                    cout << "Книга успешно записана\n";
                }
                else
                {
                    cout << "Не удалось записать новоую книгу\n";
                }
                break;
            }
            case 2:
                printLibrarys(firstLibrary);
                break;
            case 3:
                pushLibrarysIntoFile(firstLibrary, fdata);
                break;
            case 4:
                getInfoFromFile(firstLibrary, fdata);
                break;
            case 5:
                if (popLibrary(firstLibrary))
                {
                    cout << "Книга успешно удалена из списка\n";
                }
                else
                {
                    cout << "Ошибка, данной книги нет в списке\n";
                }
                break;
            case 6:
                if (cleanList(firstLibrary))
                {
                    cout << "Файл успешно очищен\n";
                }
                else
                {
                    cout << "Ошибка очистки файла\n";
                }
                break;
            case 7:
                if (cleanFile())
                {
                    cout << "Файл успешно очищен\n";
                }
                else
                {
                    cout << "Ошибка очистки файла\n";
                }
                break;
            case 8:
                printMenu();
                break;
            case 9:
            {
                char fio[40];
                Library* ptr = nullptr;
                cout << "Введите фамилию автора, информацию о котором, хотите получить: ";
                cin.ignore();
                cin.getline(fio, 40);
                ptr = searchLibrary(firstLibrary, fio);
                if (ptr != nullptr)
                {
                    cout << "Книга найдена, информация о книге:\n";
                    printLine();
                    cout << "Автор книги: " << ptr->authorFio.fullFio << "\n";
                    cout << "Название книги: " << ptr->title << "\n";
                    cout << "Дата публикации: " << ptr->publishing << "\n";
                    cout << "Раздел библиотеки: " << ptr->chapter << "\n";
                    cout << "Происхождение: " << ptr->origin << "\n";
                    cout << "Наличие: ";
                    ptr->availability == 0 ? cout << "Книги нет в наличии\n" : cout << "Книга есть в наличии\n";
                    printLine();
                }
                else
                {
                    cout << "Книги нет в списке\n";
                }
                break;
            }
            case 0:
                exit(0);
                break;
            default:
                cout << "Ошибка ввода\n";
                break;
            }
        }
        else
        {
            cout << "Ошибка ввода\n";
        }
    }
}

void printMenu()
{
    printLine();
    cout << "1 - Добавить новую книгу\n";
    cout << "2 - Вывести все записанные книги\n";
    cout << "3 - Записать библиотеку в файл\n";
    cout << "4 - Получить информацию о библиотекке из файла\n";
    cout << "5 - Удалить книгу\n";
    cout << "6 - Очистить список\n";
    cout << "7 - Очистить файл\n";
    cout << "8 - Вывести меню в консоль\n";
    cout << "9 - Получить информацию о книге по автору\n";
    cout << "0 - Выход из программы\n";
    printLine();
}

void printLine()
{
    cout << "____________________________________________\n";
}

bool convertToInt(string line, int& userInput)
{
    int repeat = 0;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] >= '0' && line[i] <= '9')
        {
            repeat++;
        }
    }
    if (repeat == line.length())
    {
        userInput = stoi(line);
    }
    return repeat == line.length();
}

bool pushNewLibrary(Library*& firstLibrary, Library* newLibrary)
{
    Library* ptr = firstLibrary;
    if (firstLibrary == nullptr)
    {
        firstLibrary = newLibrary;
    }
    else
    {
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newLibrary;
    }
    return true;
}

void printLibrarys(Library* firstLibrary)
{
    Library* ptr = firstLibrary;
    if (firstLibrary != nullptr)
    {
        cout << "Список клиентов:\n";
        while (ptr != nullptr)
        {
            string fio = ptr->authorFio.fullFio;
            printLine();
            getShortName(ptr);
            cout << "Автор книги: " << ptr->authorFio.shortFio<< "\n";
            cout << "Название книги: " << ptr->title << "\n";
            cout << "Дата публикации: " << ptr->publishing << "\n";
            cout << "Раздел библиотеки: " << ptr->chapter << "\n";
            cout << "Происхождение: " << ptr->origin << "\n";
            cout << "Наличие: ";
            ptr->availability == 0 ? cout << "Книги нет в наличии\n" : cout << "Книга есть в наличии\n";
            for (int i = 0; i < fio.length(); i++)
            {
                ptr->authorFio.fullFio[i] = fio[i];
                ptr->authorFio.fullFio[i + 1] = '\0';
            }
            printLine();
            ptr = ptr->next;
        }
    }
    else
    {
        cout << "Список преподавателей пуст\n";
    }
}

void getShortName(Library*& ptr)
{
    char fio[40];
    int i = 0;
    for (; ptr->authorFio.fullFio[i] != ' '; i++)
    {
        fio[i] = ptr->authorFio.fullFio[i];
    }
    for (int j = 0; j < 2; j++)
    {
        fio[i] = ptr->authorFio.fullFio[i];
        i++;
    }
    int j = i;
    fio[i] = '.';
    fio[++i] = ' ';
    while (ptr->authorFio.fullFio[j] != ' ')
    {
        j++;
    }
    fio[++i] = ptr->authorFio.fullFio[++j];
    fio[++i] = '.';
    fio[++i] = '\0';
    for (int i = 0; i < sizeof(fio); i++)
    {
        ptr->authorFio.shortFio[i] = fio[i];
    }
}

void pushLibrarysIntoFile(Library* firstLibrary, fstream& fdata)
{
    Library* ptr = firstLibrary;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::app);
        if (firstLibrary != nullptr)
        {
            while (ptr != nullptr)
            {
                fdata << ptr->authorFio.fullFio << "\n" << ptr->title<< "\n" << ptr->publishing << "\n" << ptr->chapter << "\n" << ptr->origin << "\n" << ptr->availability << "\n";
                ptr = ptr->next;
            }
            cout << "Список успешнл записан в файл\n";
        }
        else
        {
            cout << "Список клиентов пуст, данные не записаны\n";
        }
        fdata.close();
    }
}

void getInfoFromFile(Library*& firstLibrary, fstream& fdata)
{
    Library* ptr = firstLibrary;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::in);
        if (fdata.is_open())
        {
            while (true)
            {
                int temp;
                Library* newLibrary = new Library;
                fdata.getline(newLibrary->authorFio.fullFio, 40);
                if (!fdata)
                {
                    break;
                }
                getline(fdata, newLibrary->title);
                getline(fdata, newLibrary->publishing);
                getline(fdata, newLibrary->chapter);
                getline(fdata, newLibrary->origin);
                fdata >> newLibrary->availability;
                pushNewLibrary(firstLibrary, newLibrary);
            }
            fdata.close();
            cout << "Данные успешно получены из файла\n";
        }
        else
        {
            cout << "Ошибка открытия файла, файл не создан\n";
        }
    }
}

bool popLibrary(Library*& firstLibrary)
{
    char fio[40];
    cout << "Введите фамилию автора которого хотите удалить: ";
    cin.ignore();
    cin.getline(fio, 40);
    Library* ptr = searchLibrary(firstLibrary, fio);
    if (ptr != nullptr)
    {
        Library* temp = ptr;
        if (firstLibrary != ptr)
        {
            ptr = ptr->next;
        }
        else
        {
            firstLibrary = firstLibrary->next;
        }
        delete(temp);
    }
    return ptr != nullptr;
}

bool cleanList(Library*& firstLibrary)
{
    Library* ptr = firstLibrary, * prev;
    if (firstLibrary != nullptr)
    {
        while (ptr != nullptr)
        {
            prev = ptr;
            ptr = ptr->next;
            delete(prev);
        }
        firstLibrary = nullptr;
    }
    else
    {
        cout << "Список книг пуст\n";
    }
    return true;
}

bool cleanFile()
{
    remove("data.bin");
    return true;
}

Library* searchLibrary(Library* firstLibrary, char fio[])
{
    Library* ptr = firstLibrary;
    int repeat = 0;
    if (firstLibrary != nullptr)
    {
        while (ptr != nullptr)
        {
            for (int i = 0; fio[i] != '\0'; i++)
            {
                if (fio[i] == ptr->authorFio.fullFio[i])
                {
                    repeat++;
                }
            }
            if (sizeof(fio) - 1 == repeat)
            {
                break;
            }
            else
            {
                repeat = 0;
            }
            ptr = ptr->next;
        }
    }
    else
    {
        cout << "Список книг пуст\n";
    }
    return ptr;
}