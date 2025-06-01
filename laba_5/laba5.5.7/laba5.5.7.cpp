#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

union Supplier
{
    char fullName[40];
    char shortName[40];
};

struct Warehouse
{
    Supplier supplierName;
    string title;
    int price;
    int quantity;
    int percentageOfPremium;
    Warehouse* next;

    Warehouse()
    {
        next = nullptr;
    }

};

void printLine();

void printMenu();

bool convertToInt(string line, int& userInput);

bool pushNewWarehouse(Warehouse*& firstWarehouse, Warehouse* newWarehouse);

void printWarehouses(Warehouse* firstWarehouse);

void pushWarehousesIntoFile(Warehouse* firstWarehouse, fstream& fdata);

void getInfoFromFile(Warehouse*& firstWarehouse, fstream& fdata);

bool popWarehouse(Warehouse*& firstWarehouse);

bool cleanList(Warehouse*& firstWarehouse);

void getShortName(Warehouse*& ptr);

bool cleanFile();

Warehouse* searchWarehouse(Warehouse* firstWarehouse, char title[]);

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string line;
    int userInput;
    fstream fdata;
    Warehouse* firstWarehouse = nullptr;
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
                Warehouse* newWarehouse = new Warehouse;
                cout << "Введите информацию о новом товаре:\n";
                cout << "Наименование товара: ";
                cin.ignore();
                getline(cin, newWarehouse->title);
                cout << "Введите название постовщика: ";
                cin.getline(newWarehouse->supplierName.fullName ,40);
                cout << "Цена товара: ";
                cin >> newWarehouse->price;
                cout << "Количество: ";
                cin >> newWarehouse->quantity;
                cout << "Процент торговой надбавки: ";
                cin >> newWarehouse->percentageOfPremium;
                if (pushNewWarehouse(firstWarehouse, newWarehouse))
                {
                    cout << "Товар успешно записана\n";
                }
                else
                {
                    cout << "Не удалось записать новый товар\n";
                }
                break;
            }
            case 2:
                printWarehouses(firstWarehouse);
                break;
            case 3:
                pushWarehousesIntoFile(firstWarehouse, fdata);
                break;
            case 4:
                getInfoFromFile(firstWarehouse, fdata);
                break;
            case 5:
                if (popWarehouse(firstWarehouse))
                {
                    cout << "Товар успешно удалена из списка\n";
                }
                else
                {
                    cout << "Ошибка, данного товара нет в списке\n";
                }
                break;
            case 6:
                if (cleanList(firstWarehouse))
                {
                    cout << "Список успешно очищен\n";
                }
                else
                {
                    cout << "Ошибка очистки список\n";
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
                Warehouse* ptr = nullptr;
                cout << "Введите наименование товара, информацию о котором хотите получить: ";
                cin.ignore();
                cin.getline(title, 40);
                ptr = searchWarehouse(firstWarehouse, title);
                if (ptr != nullptr)
                {
                    cout << "Товар успешно найден, информация о товаре:\n";
                    printLine();
                    cout << "Поставщик: " <<ptr->supplierName.fullName << "\n";
                    cout << "Название товара: " << ptr->title << "\n";
                    cout << "Цена: " << ptr->price << "\n";
                    cout << "Количество товара: " << ptr->quantity << "\n";
                    cout << "Торговая надбавка: " << ptr->percentageOfPremium << "\n";
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
    cout << "1 - Добавить новый товар\n";
    cout << "2 - Вывести все записанные товары\n";
    cout << "3 - Записать список товаров в файл\n";
    cout << "4 - Получить информацию о складе из файла\n";
    cout << "5 - Удалить товар\n";
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

bool pushNewWarehouse(Warehouse*& firstWarehouse, Warehouse* newWarehouse)
{
    Warehouse* ptr = firstWarehouse;
    if (firstWarehouse == nullptr)
    {
        firstWarehouse = newWarehouse;
    }
    else
    {
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newWarehouse;
    }
    return true;
}

void printWarehouses(Warehouse* firstWarehouse)
{
    Warehouse* ptr = firstWarehouse;
    if (firstWarehouse != nullptr)
    {
        cout << "Список клиентов:\n";
        while (ptr != nullptr)
        {
            string fio = ptr->supplierName.fullName;
            printLine();
            getShortName(ptr);
            cout << "Поставщик: " << ptr->supplierName.fullName << "\n";
            cout << "Название товара: " << ptr->title << "\n";
            cout << "Цена: " << ptr->price << "\n";
            cout << "Количество товара: " << ptr->quantity << "\n";
            cout << "Торговая надбавка: " << ptr->percentageOfPremium << "\n";
            for (int i = 0; i < fio.length(); i++)
            {
                ptr->supplierName.fullName[i] = fio[i];
                ptr->supplierName.fullName[i + 1] = '\0';
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

void getShortName(Warehouse*& ptr)
{
    char fio[40];
    int i = 0;
    for (; ptr->supplierName.fullName[i] != ' '; i++)
    {
        fio[i] = ptr->supplierName.fullName[i];
    }
    for (int j = 0; j < 2; j++)
    {
        fio[i] = ptr->supplierName.fullName[i];
        i++;
    }
    int j = i;
    fio[i] = '.';
    fio[++i] = '\0';
    for (int i = 0; i < sizeof(fio); i++)
    {
        ptr->supplierName.shortName[i] = fio[i];
    }
}

void pushWarehousesIntoFile(Warehouse* firstWarehouse, fstream& fdata)
{
    Warehouse* ptr = firstWarehouse;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::app);
        if (firstWarehouse != nullptr)
        {
            while (ptr != nullptr)
            {
                fdata << ptr->supplierName.fullName << "\n" << ptr->title << "\n" << ptr->price << "\n" << ptr->quantity << "\n" << ptr->percentageOfPremium << "\n";
                ptr = ptr->next;
            }
            cout << "Список успешно записан в файл\n";
        }
        else
        {
            cout << "Склад пуст, данные не записаны\n";
        }
        fdata.close();
    }
}

void getInfoFromFile(Warehouse*& firstWarehouse, fstream& fdata)
{
    Warehouse* ptr = firstWarehouse;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::in);
        if (fdata.is_open())
        {
            while (true)
            {
                int temp;
                Warehouse* newWarehouse = new Warehouse;
                fdata.getline(newWarehouse->supplierName.fullName, 40);
                if (!fdata)
                {
                    break;
                }
                getline(fdata, newWarehouse->title);
                fdata >> newWarehouse->price;
                fdata >> newWarehouse->quantity;
                fdata >> newWarehouse->percentageOfPremium;
                pushNewWarehouse(firstWarehouse, newWarehouse);
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

bool popWarehouse(Warehouse*& firstWarehouse)
{
    char title[40];
    cout << "Введите наименование товара, который хотите удалить: ";
    cin.ignore();
    cin.getline(title, 40);
    Warehouse* ptr = searchWarehouse(firstWarehouse, title);
    if (ptr != nullptr)
    {
        Warehouse* temp = ptr;
        if (firstWarehouse != ptr)
        {
            ptr = ptr->next;
        }
        else
        {
            firstWarehouse = firstWarehouse->next;
        }
        delete(temp);
    }
    return ptr != nullptr;
}

bool cleanList(Warehouse*& firstWarehouse)
{
    Warehouse* ptr = firstWarehouse, * prev;
    if (firstWarehouse != nullptr)
    {
        while (ptr != nullptr)
        {
            prev = ptr;
            ptr = ptr->next;
            delete(prev);
        }
        firstWarehouse = nullptr;
    }
    else
    {
        cout << "Склад пуст\n";
    }
    return true;
}

bool cleanFile()
{
    remove("data.bin");
    return true;
}

Warehouse* searchWarehouse(Warehouse* firstWarehouse, char title[])
{
    Warehouse* ptr = firstWarehouse;
    int repeat = 0;
    if (firstWarehouse != nullptr)
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
        cout << "Склад пуст\n";
    }
    return ptr;
}