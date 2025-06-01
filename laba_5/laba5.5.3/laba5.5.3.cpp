#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

union Fio
{
    char fullFio[40];
    char shortFio[40];
};

struct Pawnshop
{
    Fio fio;
    int age;
    string title;
    string date;
    int price;
    int pledge;
    int shelfLife;
    Pawnshop* next;

    Pawnshop()
    {
        next = nullptr;
    }
};

void printLine();

void printMenu();

bool convertToInt(string line, int& userInput);

bool pushNewPawnshop(Pawnshop*& firstPawnshop, Pawnshop* newPawnshop);

void printPawnshops(Pawnshop* firstPawnshop);

void pushPawnshopsIntoFile(Pawnshop* firstPawnshop, fstream& fdata);

void getInfoFromFile(Pawnshop*& firstPawnshop, fstream& fdata);

bool popPawnshop(Pawnshop*& firstPawnshop);

bool cleanList(Pawnshop*& firstPawnshop);

void getShortName(Pawnshop*& ptr);

bool cleanFile();

Pawnshop* searchPawnshop(Pawnshop* firstPawnshop, char title[]);

int main() {
    string line;
    int userInput;
    fstream fdata;
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printMenu();
    Pawnshop* firstPawnshop = nullptr;
    while (true)
    {
        cin >> line;
        if (convertToInt(line, userInput))
        {
            switch (userInput)
            {
            case 1:
            {
                Pawnshop* newPawnshop = new Pawnshop;
                cout << "Введите информацию о клиенте:\n";
                cout << "Введите фио клиента: ";
                cin.ignore();
                cin.getline(newPawnshop->fio.fullFio, 30);
                cout << "Введите название товара: ";
                getline(cin, newPawnshop->title);
                cout << "Введите дату сдачи под залог(в формате дд.мм.гггг): ";
                getline(cin, newPawnshop->date);
                cout << "Введите возвраст клиента: ";
                cin >> newPawnshop->age;
                cout << "Введите оценочную стоимость товара: ";
                cin >> newPawnshop->price;
                cout << "Введите сумму, выданную под залог: ";
                cin >> newPawnshop->pledge;
                cout << "Введите дату хранение (n месяцев): ";
                cin >> newPawnshop->shelfLife;
                if (pushNewPawnshop(firstPawnshop, newPawnshop))
                {
                    cout << "Клиент успешно записан\n";
                }
                else
                {
                    cout << "Не удалось записать нового клиента\n";
                }
                break;
            }
            case 2:
                printPawnshops(firstPawnshop);
                break;
            case 3:
                pushPawnshopsIntoFile(firstPawnshop, fdata);
                break;
            case 4:
                getInfoFromFile(firstPawnshop, fdata);
                break;
            case 5:
                if (popPawnshop(firstPawnshop))
                {
                    cout << "Клиент успешно удален из списка\n";
                }
                else
                {
                    cout << "Ошибка, клиента нет в списке\n";
                }
                break;
            case 6:
                if (cleanList(firstPawnshop))
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
                char title[40];
                Pawnshop* ptr = nullptr;
                cout << "Введите название товара, о котором хотите получить информацию: ";
                cin.ignore();
                cin.getline(title, 40);
                ptr = searchPawnshop(firstPawnshop, title);
                if (ptr != nullptr)
                {
                    printLine();
                    cout << "Фио клиента: " << ptr->fio.shortFio << "\n";
                    cout << "Возраст клиента: " << ptr->age << " лет\n";
                    cout << "Наименование товара: " << ptr->title << "\n";
                    cout << "Оценочная стоимость: " << ptr->price << "\n";
                    cout << "Сумма под залогом: " << ptr->pledge << "\n";
                    cout << "Дата сдачи под залог: " << ptr->date << "\n";
                    cout << "Срок хранения: " << ptr->shelfLife << " месяцев\n";
                    printLine();
                }
                else
                {
                    cout << "Товара нет в списке\n";
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
    cout << "1 - Добавить нового клиента\n";
    cout << "2 - Вывести всех записанных клиентов\n";
    cout << "3 - Записать клиентов в файл\n";
    cout << "4 - Получить информацию о клиентах из файла\n";
    cout << "5 - Удалить клиента\n";
    cout << "6 - Очистить список\n";
    cout << "7 - Очистить файл\n";
    cout << "8 - Вывести меню в консоль\n";
    cout << "9 - Получить информацию о товаре по названию\n";
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

bool pushNewPawnshop(Pawnshop*& firstPawnshop, Pawnshop* newPawnshop)
{
    Pawnshop* ptr = firstPawnshop;
    if (firstPawnshop == nullptr)
    {
        firstPawnshop = newPawnshop;
    }
    else
    {
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newPawnshop;
    }
    return true;
}

void printPawnshops(Pawnshop* firstPawnshop)
{
    Pawnshop* ptr = firstPawnshop;
    if (firstPawnshop != nullptr)
    {
        cout << "Список клиентов:\n";
        while (ptr != nullptr)
        {
            string fio = ptr->fio.fullFio;
            printLine();
            getShortName(ptr);
            cout << "Фио клиента: " << ptr->fio.shortFio << "\n";
            cout << "Возраст клиента: " << ptr->age << " лет\n";
            cout << "Наименование товара: " << ptr->title << "\n";
            cout << "Оценочная стоимость: " << ptr->price << "\n";
            cout << "Сумма под залогом: " << ptr->pledge << "\n";
            cout << "Дата сдачи под залог: " << ptr->date << "\n";
            cout << "Срок хранения: " << ptr->shelfLife << " месяцев\n";
            for (int i = 0; i < fio.length(); i++)
            {
                ptr->fio.fullFio[i] = fio[i];
                ptr->fio.fullFio[i + 1] = '\0';
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

void getShortName(Pawnshop*& ptr)
{
    char fio[40];
    int i = 0;
    for (; ptr->fio.fullFio[i] != ' '; i++)
    {
        fio[i] = ptr->fio.fullFio[i];
    }
    for (int j = 0; j < 2; j++)
    {
        fio[i] = ptr->fio.fullFio[i];
        i++;
    }
    int j = i;
    fio[i] = '.';
    fio[++i] = ' ';
    while (ptr->fio.fullFio[j] != ' ')
    {
        j++;
    }
    fio[++i] = ptr->fio.fullFio[++j];
    fio[++i] = '.';
    fio[++i] = '\0';
    for (int i = 0; i < sizeof(fio); i++)
    {
        ptr->fio.shortFio[i] = fio[i];
    }
}

void pushPawnshopsIntoFile(Pawnshop* firstPawnshop, fstream& fdata)
{
    Pawnshop* ptr = firstPawnshop;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::app);
        if (firstPawnshop != nullptr)
        {
            while (ptr != nullptr)
            {
                fdata << ptr->fio.fullFio << "\n" << ptr->age << "\n" << ptr->date << "\n" << ptr->pledge << "\n" << ptr->price << "\n" << ptr->shelfLife << "\n" << ptr->title << "\n";
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

void getInfoFromFile(Pawnshop*& firstPawnshop, fstream& fdata)
{
    Pawnshop* ptr = firstPawnshop;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::in);
        if (fdata.is_open())
        {
            while (true)
            {
                Pawnshop* newPawnshop = new Pawnshop;
                fdata.getline(newPawnshop->fio.fullFio, 40);
                if (!fdata)
                {
                    break;
                }
                int temp;
                fdata >> temp;
                newPawnshop->age = temp;
                fdata.ignore();
                getline(fdata, newPawnshop->date);
                fdata >> temp;
                newPawnshop->pledge = temp;
                fdata >> temp;
                newPawnshop->price = temp;
                fdata >> temp;
                newPawnshop->shelfLife = temp;
                fdata.ignore();
                getline(fdata, newPawnshop->title);
                pushNewPawnshop(firstPawnshop, newPawnshop);
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

bool popPawnshop(Pawnshop*& firstPawnshop)
{
    char title[40];
    cout << "Введите наименование товара который хотите удалить: ";
    cin.ignore();
    cin.getline(title, 40);
    Pawnshop* ptr = searchPawnshop(firstPawnshop, title);
    if (ptr != nullptr)
    {
        Pawnshop* temp = ptr;
        if (firstPawnshop != ptr)
        {
            ptr = ptr->next;
        }
        else
        {
            firstPawnshop = firstPawnshop->next;
        }
        delete(temp);
    }
    return ptr != nullptr;
}

bool cleanList(Pawnshop*& firstPawnshop)
{
    Pawnshop* ptr = firstPawnshop, * prev;
    if (firstPawnshop != nullptr)
    {
        while (ptr != nullptr)
        {
            prev = ptr;
            ptr = ptr->next;
            delete(prev);
        }
        firstPawnshop = nullptr;
    }
    else
    {
        cout << "Список клиентов пуст\n";
    }
    return true;
}

bool cleanFile()
{
    remove("data.bin");
    return true;
}

Pawnshop* searchPawnshop(Pawnshop* firstPawnshop, char title[])
{
    Pawnshop* ptr = firstPawnshop;
    int repeat = 0;
    if (firstPawnshop != nullptr)
    {
        while (ptr != nullptr)
        {
            for (int i = 0; title[i] != '\0'; i++)
            {
                if (title[i] == ptr->title[i])
                {
                    repeat++;
                }
            }
            if (ptr->title.length() == repeat)
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
        cout << "Список преподавателей пуст\n";
    }
    return ptr;
}