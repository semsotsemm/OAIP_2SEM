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

struct Teacher 
{
    Fio name;
    string examName;
    string examDate;
    Teacher* next;

    Teacher() 
    {
        next = nullptr;
    }
};

void printLine();

void printMenu();

bool convertToInt(string line, int& userInput);

bool pushNewTeacher(Teacher*& firstTeacher, Teacher* newTeacher);

void printTeachers(Teacher* firstTeacher);

void pushTeachersIntoFile(Teacher* firstTeacher, fstream& fdata);

void getInfoFromFile(Teacher*& firstTeacher, fstream& fdata);

bool popTeacher(Teacher*& firstTeacher);

bool cleanList(Teacher*& firstTeacher);

void getShortName(Teacher*& ptr);

bool cleanFile();

Teacher* searchTeacher(Teacher* firstTeacher, char fio[]);

int main() {
    string line;
    int userInput;
    fstream fdata;
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    printMenu();
    Teacher* firstTeacher = nullptr;
    while (true)
    {
        cin >> line;
        if (convertToInt(line, userInput))
        {
            switch (userInput)
            {
            case 1:
            {
                Teacher* newTeacher = new Teacher;
                cout << "Введите информацию о учителе:\n";
                cout << "Введите фио: ";
                cin.ignore();
                cin.getline(newTeacher->name.fullFio, 30);
                cout << "Введите название экзамена: ";
                cin >> newTeacher->examName;
                cout << "Введите дату проведения экзамена: ";
                cin >> newTeacher->examDate;
                if (pushNewTeacher(firstTeacher, newTeacher))
                {
                    cout << "Учитель успешно записан\n";
                }
                else
                {
                    cout << "Не удалось записать нового преподавателя\n";
                }
                break;
            }
            case 2:
                printTeachers(firstTeacher);
                break;
            case 3:
                pushTeachersIntoFile(firstTeacher, fdata);
                break;
            case 4:
                getInfoFromFile(firstTeacher, fdata);
                break;
            case 5:
                if (popTeacher(firstTeacher))
                {
                    cout << "Элемент успешно удален из списка\n";
                }
                else
                {
                    cout << "Ошибка, преподавателя нет в списке\n";
                }
                break;
            case 6:
                if (cleanList(firstTeacher))
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
                Teacher* ptr = nullptr;
                cout << "Введите фамилию преподавателя о котором хотите получить информацию: ";
                cin.ignore();
                cin.getline(fio, 40);
                ptr = searchTeacher(firstTeacher, fio);
                if (ptr != nullptr)
                {
                    printLine();
                    cout << "Преподаватель найден:\n";
                    cout << "Фио: " << ptr->name.fullFio << "\n";
                    cout << "Название экзамена: " << ptr->examName << "\n";
                    cout << "Дата проведения экзамена: " << ptr->examDate << "\n";
                    printLine();
                }
                else
                {
                    cout << "Преподавателя нет в списке\n";
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
    cout << "1 - Добавить нового преподавателя\n";
    cout << "2 - Вывести всех записанных преподавателей\n";
    cout << "3 - Записать преподавателей в файл\n";
    cout << "4 - Получить информацию о преподавателях из файла\n";
    cout << "5 - Удалить преподавателя\n";
    cout << "6 - Очистить список\n";
    cout << "7 - Очистить файл\n";
    cout << "8 - Вывести меню в консоль\n";
    cout << "9 - Получить информацию о преподавателе\n";
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

bool pushNewTeacher(Teacher*& firstTeacher, Teacher* newTeacher) 
{
    Teacher *ptr = firstTeacher;
    if (firstTeacher == nullptr)
    {
        firstTeacher = newTeacher;
    }
    else
    {
        while (ptr->next != nullptr)
        {
            ptr = ptr->next;
        }
        ptr->next = newTeacher;
    }
    return true;
}

void printTeachers(Teacher* firstTeacher)
{
    Teacher* ptr = firstTeacher;
    if (firstTeacher != nullptr)
    {
        cout << "Список преподавателей:\n";
        while (ptr != nullptr)
        {
            string fio = ptr->name.fullFio;
            printLine();
            getShortName(ptr);
            cout << "Фио: " << ptr->name.shortFio << "\n";
            cout << "Название экзамена: " << ptr->examName << "\n";
            cout << "Дата проведения экзамена: " << ptr->examDate << "\n";
            printLine();
            for (int i = 0; i < fio.length(); i++)
            {
                ptr->name.fullFio[i] = fio[i];
                ptr->name.fullFio[i + 1] = '\0';
            }
            ptr = ptr->next;
        }
    }
    else
    {
        cout << "Список преподавателей пуст\n";
    }
}

void getShortName(Teacher*& ptr)
{
    char fio[40];
    int i = 0;
    for (; ptr->name.fullFio[i] != ' '; i++)
    {
        fio[i] = ptr->name.fullFio[i];
    }
    for (int j = 0; j < 2; j++)
    {
        fio[i] = ptr->name.fullFio[i];
        i++;
    }
    int j = i;
    fio[i] = '.';
    fio[++i] = ' ';
    while (ptr->name.fullFio[j] != ' ')
    {
        j++;
    }
    fio[++i] = ptr->name.fullFio[++j];
    fio[++i] = '.';
    fio[++i] = '\0';
    for (int i = 0; i < sizeof(fio); i++)
    {
        ptr->name.shortFio[i] = fio[i];
    }
}

void pushTeachersIntoFile(Teacher* firstTeacher, fstream& fdata)
{
    Teacher* ptr = firstTeacher;
    if (!fdata.is_open()) 
    {
        fdata.open("data.bin", ios::app);
        if (firstTeacher != nullptr)
        {
            while (ptr != nullptr)
            {
                fdata << ptr->name.fullFio << "\n" << ptr->examName << "\n" << ptr->examDate << "\n";
                ptr = ptr->next;
            }
            cout << "Список успешнл записан в файл\n";
        }
        else
        {
            cout << "Список преподавателей пуст, данные не записаны\n";
        }
        fdata.close();
    }
}

void getInfoFromFile(Teacher*& firstTeacher, fstream& fdata)
{
    Teacher* ptr = firstTeacher;
    if (!fdata.is_open())
    {
        fdata.open("data.bin", ios::in);
        if (fdata.is_open())
        {
            while (true)
            {
                Teacher* newTeacher = new Teacher;
                fdata.getline(newTeacher->name.fullFio, 40);
                if (!fdata)
                {
                    break;
                }
                getline(fdata, newTeacher->examName);
                getline(fdata, newTeacher->examDate);
                pushNewTeacher(firstTeacher, newTeacher);
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

bool popTeacher(Teacher*& firstTeacher)
{
    char fio[40];
    cout << "Введите фамилию преподавателя которого хотите удалить из списка: ";
    cin.ignore();
    cin.getline(fio, 40);
    Teacher* ptr = searchTeacher(firstTeacher, fio);
    if (ptr != nullptr)
    {
        Teacher* temp = ptr;
        if (firstTeacher != ptr)
        {
            ptr = ptr->next;
        }
        else
        {
            firstTeacher = firstTeacher->next;
        }
        delete(temp);
    }
    return ptr != nullptr;
}

bool cleanList(Teacher*& firstTeacher)
{
    Teacher* ptr = firstTeacher,* prev;
    if (firstTeacher != nullptr)
    {
        while (ptr != nullptr)
        {
            prev = ptr;
            ptr = ptr->next;
            delete(prev);
        }
        firstTeacher = nullptr;
    }
    else
    {
        cout << "Список преподавателей пуст\n";
    }
    return true;
}

bool cleanFile()
{
    remove("data.bin");
    return true;
}

Teacher* searchTeacher(Teacher* firstTeacher, char fio[])
{
    Teacher* ptr = firstTeacher;
    int repeat = 0;
    if (firstTeacher != nullptr)
    {
        while (ptr != nullptr)
        {
            for (int i = 0; i < sizeof(fio) - 1; i++)
            {
                if (fio[i] == ptr->name.fullFio[i])
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
        cout << "Список преподавателей пуст\n";
    }
    return ptr;
}