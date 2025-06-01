#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

FILE* fnewdata;
FILE* fdata;

struct numberOfClass
{
    unsigned int numOfClass : 4;
    unsigned char letterOfClass : 8;
};

enum subjects
{
    mathematics = 1,  // Математика
    physics = 2,      // Физика
    english = 3,      // Английский
    russian = 4,      // Русский
    belorussian = 5,  // Белорусский
    literature = 6,   // Литература
    chemistry = 7,    // Химия
    biology = 8,      // Биология
    history = 9,      // История
    geography = 10    // География
};

struct student
{
    int id;
    char fio[100];
    numberOfClass studentСlass;
    subjects specializedSubject;
    int grades[10];
    double averageGrades;
};

int getId();

void printSubjectOfStudent(int subject);

void printSubjectList();

void printTab(int num);

void printline();

void outputStudent();

void inputStudent();

void deleteStudent();

void searchStudent();

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int userInput;
    setlocale(LC_CTYPE, "Russian");
    cout << "Меню:\n" << "1 - Ввод данных о новом ученике\n" << "2 - Вывод информации о всех учениках\n";
    cout << "3 - Удаление ученика\n" << "4 - Поиск ученика по стажу работы\n" << "0 - Выход из программы\n";
    do
    {
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            inputStudent();
            break;
        case 2:
            outputStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            searchStudent();
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

void printSubjectList()
{
    cout << "1 - Математика\n";
    cout << "2 - Физика\n";
    cout << "3 - Английский\n";
    cout << "4 - Русский язык\n";
    cout << "5 - Белорусский язык\n";
    cout << "6 - Литература\n";
    cout << "7 - Химия\n";
    cout << "8 - Биология\n";
    cout << "9 - История\n";
    cout << "10 - География\n";
}

int getId()
{
    student buf;
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

void outputStudent()
{
    student buf;
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            printline();
            cout << "Id: " << buf.id << "\n";
            cout << "Фио ученика: " << buf.fio << "\n";
            cout << "Класс " << buf.studentСlass.numOfClass << buf.studentСlass.letterOfClass << "\n";
            cout << "Профильный предмет: ";
            printSubjectOfStudent(buf.specializedSubject);
            cout << "\n";
            cout << "Оценки ученика:\n";
            for (int i = 0; i < 10; i++)
            {
                printSubjectOfStudent(i + 1);
                cout << ": " << buf.grades[i] << "\n";
            }
            cout << "Средний балл ученика: " << buf.averageGrades << "\n";
        }
        fclose(fdata);
        printline();
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void inputStudent()
{
    int size;
    student buf;
    cout << "Введите сколько новых сотрудников хотите записать: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        buf.id = getId();
        fopen_s(&fdata, "data.bin", "ab");
        cout << "Введите фио ученика: ";
        cin.ignore();
        cin.getline(buf.fio, 100);
        cout << "Введите номер класса ученика: ";
        int numOfClass;
        cin >> numOfClass;
        buf.studentСlass.numOfClass = numOfClass;
        cout << "Ввдеите букву класса ученика: ";
        unsigned char letterOfClass;
        cin >> letterOfClass;
        buf.studentСlass.letterOfClass = letterOfClass;
        cout << "Введите профильный предмет ученика:\n";
        printSubjectList();
        int subj = -1;
        while (!(subj > 0 && subj < 11))
        {
            cin >> subj;
            switch (subj)
            {
            case 1:
                buf.specializedSubject = mathematics;
                break;
            case 2:
                buf.specializedSubject = physics;
                break;
            case 3:
                buf.specializedSubject = english;
                break;
            case 4:
                buf.specializedSubject = russian;
                break;
            case 5:
                buf.specializedSubject = belorussian;
                break;
            case 6:
                buf.specializedSubject = literature;
                break;
            case 7:
                buf.specializedSubject = chemistry;
                break;
            case 8:
                buf.specializedSubject = biology;
                break;
            case 9:
                buf.specializedSubject = history;
                break;
            case 10:
                buf.specializedSubject = geography;
                break;
            default:
                cout << "Ошибка ввода\n";
                break;
            }
        }
        cout << "Введите оценки ученика по всем предметам по порядку:\n";
        printSubjectList();
        int sum = 0;
        for (int i = 0; i < 10; i++)
        {
            cin >> buf.grades[i];
            sum += buf.grades[i];
        }
        buf.averageGrades = sum / 10;
        fwrite(&buf, sizeof(buf), 1, fdata);
        fclose(fdata);
    }
}

void deleteStudent()
{
    student buf;
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

void searchStudent()
{
    student buf;
    string fio;
    cout << "Введите фио ученика: ";
    cin.ignore();
    getline(cin, fio);
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            if (buf.fio == fio)
            {
                printline();
                cout << "Id: " << buf.id << "\n";
                cout << "Фио ученика: " << buf.fio << "\n";
                cout << "Класс " << buf.studentСlass.numOfClass << buf.studentСlass.letterOfClass << "\n";
                cout << "Профильный предмет: ";
                printSubjectOfStudent(buf.specializedSubject);
                cout << "\n";
                cout << "Оценки ученика:\n";
                for (int i = 0; i < 10; i++)
                {
                    printSubjectOfStudent(i + 1);
                    cout << ": " << buf.grades[i] << "\n";
                }
                cout << "Средний балл ученика: " << buf.averageGrades << "\n";
                printline();
            }
        }
    }
}

void printSubjectOfStudent(int subject)
{

    switch (subject)
    {
    case 1:
        cout << "Математика";
        break;
    case 2:
        cout << "Физика";
        break;
    case 3:
        cout << "Ангилийский язык";
        break;
    case 4:
        cout << "Русский язык";
        break;
    case 5:
        cout << "Белорусский язык";
        break;
    case 6:
        cout << "Литература";
        break;
    case 7:
        cout << "Химия";
        break;
    case 8:
        cout << "Биология";
        break;
    case 9:
        cout << "История";
        break;
    case 10:
        cout << "География";
        break;
    default:
        break;
    }
}