#include <iostream>

using namespace std;

void printLine() \
{
    cout << "_______________________\n";
}

FILE* fdata, * gdata;

struct Num
{
    int value;
    Num* next;
};

struct Symbol
{
    char value;
    Symbol* next;
};

Num* firstnum = nullptr;

Symbol* firstsymb = nullptr;

void showMenu()
{
    printLine();
    cout << "Меню:\n" << "1 - Заполнить случайными символами файл f\n";
    cout << "2 - Заполнить файл g\n" << "0 - Выход из программы\n";
    printLine();
}

void fillFFile()
{
    srand(time(0));
    int colum, row, symbolOrNumber;
    char symbol;
    cout << "Укажите количество строк: ";
    cin >> colum;
    cout << "Укажите количество символов в каждой строке: ";
    cin >> row;
    if (!fopen_s(&fdata, "filef.txt", "w"))
    {
        for (int i = 0; i < colum; i++)
        {
            for (int i = 0; i < row; i++)
            {
                symbolOrNumber = rand() % 3;
                if (symbolOrNumber == 0)
                {
                    symbol = 65 + rand() % 26;
                }
                else if (symbolOrNumber == 1)
                {
                    symbol = 97 + rand() % 26;
                }
                else
                {
                    symbol = 48 + rand() % 10;
                }
                fwrite(&symbol, sizeof(char), 1, fdata);
            }
            fwrite("\n", sizeof(char), 1, fdata);
        }
        fclose(fdata);
    }
    else
    {
        cout << "Ошибка открытия файла f\n";
    }
}

void readLine(char symbol)
{
    Num* numbers;
    Symbol* symbols;
    Num* ptrForNum = firstnum;
    Symbol* ptrForSymbol = firstsymb;
    while (symbol != '\n')
    {
        if (symbol >= '0' && symbol <= '9')
        {
            if (ptrForNum == nullptr)
            {
                numbers = new Num;
                numbers->value = symbol;
                numbers->next = nullptr;
                firstnum = numbers;
                ptrForNum = firstnum;
            }
            else
            {
                numbers = new Num;
                numbers->value = symbol;
                numbers->next = nullptr;
                ptrForNum->next = numbers;
                ptrForNum = ptrForNum->next;
            }
        }
        else
        {
            if (ptrForSymbol == nullptr)
            {
                symbols = new Symbol;
                symbols->value = symbol;
                symbols->next = nullptr;
                firstsymb = symbols;
                ptrForSymbol = firstsymb;
            }
            else
            {
                symbols = new Symbol;
                symbols->value = symbol;
                symbols->next = nullptr;
                ptrForSymbol->next = symbols;
                ptrForSymbol = ptrForSymbol->next;
            }
        }
        fread(&symbol, sizeof(char), 1, fdata);
    }
}

void fillGFile()
{
    char symbol;
    if (!fopen_s(&fdata, "filef.txt", "r") && !fopen_s(&gdata, "fileg.txt", "w"))
    {
        while (fread(&symbol, sizeof(char), 1, fdata))
        {
            readLine(symbol);
            while (firstsymb != nullptr)
            {
                fwrite(&(firstsymb->value), sizeof(char), 1, gdata);
                Symbol* temp;
                temp = firstsymb;
                firstsymb = firstsymb->next;
                delete(temp);
            }
            while (firstnum != nullptr)
            {
                fwrite(&(firstnum->value), sizeof(char), 1, gdata);
                Num* temp;
                temp = firstnum;
                firstnum = firstnum->next;
                delete(temp);
            }
            fwrite("\n", sizeof(char), 1, gdata);
        }
        fclose(fdata);
        fclose(gdata);
    }
    else
    {
        cout << "Ошибка, файл f не заполенен";
    }
    cout << "Файл успешно заполен\n";
}

int main()
{
    int userInput = 1;
    firstnum = nullptr;
    firstsymb = nullptr;
    setlocale(LC_CTYPE, "Russian");
    showMenu();
    while (userInput != 0)
    {
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            fillFFile();
            break;
        case 2:
            fillGFile();
            break;
        case 0:
            break;
        default:
            cout << "Ошибка ввода";
            break;
        }
        cout << "Что дальше ?\n";
    }
}