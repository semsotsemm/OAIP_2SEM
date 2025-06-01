#include <iostream>
#include <windows.h>

using namespace std;

FILE* fnewdata;
FILE* fdata;

struct date
{
    unsigned int day : 5;
    unsigned int mouth : 4;
    unsigned int year : 11;
};

enum job
{
    manager = 1,               // Менеджер
    engineer = 2,              // Инженер
    accountant = 3,            // Бухгалтер
    hr_specialist = 4,         // Специалист по кадрам
    software_developer = 5,    // Разработчик ПО
    sales_representative = 6,  // Торговый представитель
    marketing_analyst = 7,     // Маркетинговый аналитик
    ceo = 8,                   // Генеральный директор
    cto = 9,                   // Технический директор
    intern = 10                // Стажер
};

struct worker
{
    int id;
    char fio[100];
    char education[100];
    char speciality[100];
    char subdivision[100];
    job jobTitle;
    int salary;
    date dateReceipt;
};

int getId();

void printTitleList();

void printTab(int num);

void printline();

void outputWorker();

void inputWorker();

void deleteWorker();

void searchWorker();

void printUserTitle(int title);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int userInput;
    setlocale(LC_CTYPE, "Russian");
    cout << "Меню:\n" << "1 - Ввод данных о новом сотруднике\n" << "2 - Вывод информации о всех сотрудниках\n";
    cout << "3 - Увольнение сотрудника\n" << "4 - Поиск сотрудника по стажу работы\n" << "0 - Выход из программы\n";
    do
    {
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            inputWorker();
            break;
        case 2:
            outputWorker();
            break;
        case 3:
            deleteWorker();
            break;
        case 4:
            searchWorker();
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

void printTitleList()
{
    cout << "1 - Менеджер\n";
    cout << "2 - Инженер\n";
    cout << "3 - Бухгалтер\n";
    cout << "4 - Специалист по кадрам\n";
    cout << "5 - Разработчик ПО\n";
    cout << "6 - Торговый представитель\n";
    cout << "7 - Маркетинговый аналитик\n";
    cout << "8 - Генеральный директор\n";
    cout << "9 - Технический директор\n";
    cout << "10 - Стажер\n";
}

int getId()
{
    worker buf;
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

void printtab(int num)
{
    for (int i = 0; i < num; i++)
    {
        cout << "\t";
    }
}

void printline()
{
    cout << "_________________________________________________________________________________________________________________________________________________________________\n";
}

void outputWorker()
{
    worker buf;
    cout << "id |" << "\tФио сотрудника\t\t|" << "Образование\t|" << "\tСпециальность\t|";
    cout << "\tПодразделение\t|" << "\tДолжность\t|" << "Оклад\t|" << "  Дата поступления на работу\t|\n";
    printline();
    if (!fopen_s(&fdata, "data.bin", "rb"))
    {
        while (fread(&buf, sizeof(buf), 1, fdata))
        {
            cout << buf.id << "  |" << buf.fio << "\r";
            printtab(4);
            cout << "| " << buf.education << "\r";
            printtab(6);
            cout << "| " << buf.speciality << "\r";
            printtab(9);
            cout << "| " << buf.subdivision << "\r";
            printtab(12);
            cout << "| ";
            printUserTitle(buf.jobTitle);
            cout << "\r";
            printtab(15);
            cout << "| " << buf.salary << "\t|\t" << buf.dateReceipt.day << "." << buf.dateReceipt.mouth << "." << buf.dateReceipt.year << "\t\t|\n";
            printline();
        }
        fclose(fdata);
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

void inputWorker()
{
    int date;
    int size;
    worker buf;
    cout << "Введите сколько новых сотрудников хотите записать: ";
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        buf.id = getId();
        fopen_s(&fdata, "data.bin", "ab");
        cout << "Введите фио сотрудника: ";
        cin.ignore();
        cin.getline(buf.fio, 100);
        cout << "Введите образование сотрудника: ";
        cin.getline(buf.education, 100);
        cout << "Введите специальность сотрудника: ";
        cin.getline(buf.speciality, 100);
        cout << "Введите подразделение сотрудника: ";
        cin.getline(buf.subdivision, 100);
        cout << "Введите должность сотрудника(число от 1 до 10):\n";
        printTitleList();
        int title = -1;
        while (!(title > 0 && title < 11))
        {
            cin >> title;
            switch (title)
            {
            case 1:
                buf.jobTitle = manager;
                break;
            case 2:
                buf.jobTitle = engineer;
                break;
            case 3:
                buf.jobTitle = accountant;
                break;
            case 4:
                buf.jobTitle = hr_specialist;
                break;
            case 5:
                buf.jobTitle = software_developer;
                break;
            case 6:
                buf.jobTitle = sales_representative;
                break;
            case 7:
                buf.jobTitle = marketing_analyst;
                break;
            case 8:
                buf.jobTitle = ceo;
                break;
            case 9:
                buf.jobTitle = cto;
                break;
            case 10:
                buf.jobTitle = intern;
                break;
            default:
                cout << "Ошибка ввода\n";
                break;
            }
        }
        cout << "Введите оклад сотрудника: ";
        cin >> buf.salary;
        cout << "Введите год поступления на работу: ";
        cin >> date;
        buf.dateReceipt.year = date;
        cout << "Введите месяц поступления на работу: ";
        cin >> date;
        buf.dateReceipt.mouth = date;
        cout << "Введите день поступления на работу: ";
        cin >> date;
        buf.dateReceipt.day = date;

        fwrite(&buf, sizeof(buf), 1, fdata);
        fclose(fdata);
    };
}

void deleteWorker()
{
    worker buf;
    int index;
    cout << "Введите id работника которого хотите уволить: ";
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
        cout << "Работник успешно удален из списка\n";
    }
    else
    {
        cout << "Ошибка открытия файла\n";
    }
}

    void searchWorker()
    {
        worker buf;
        int year;
        cout << "Введите стаж работы: ";
        cin >> year;
        cout << "Информация о сотрудниках, чей стаж работы превышает " << year << " лет:\n";
        if (!fopen_s(&fdata, "data.bin", "rb"))
        {
            while (fread(&buf, sizeof(buf), 1, fdata))
            {
                if (year < 2025 - buf.dateReceipt.year)
                {
                    printline();
                    cout << "Фио сотрудн: " << buf.fio << "\nСтаж работы: " << 2025 - buf.dateReceipt.year << "\nОбразование: ";
                    cout << buf.education << "\nДолжность: ";
                    printUserTitle(buf.jobTitle);
                    cout << "\nОклад: " << buf.salary << "\nСпециальность: " << buf.speciality;
                    cout << "\nПодразделение: " << buf.subdivision << "\nid для взаимодействия: " << buf.id << "\n";
                    printline();
                }
            }
        }
    }

    void printUserTitle(int title)
    {
        switch (title)
        {
        case 1:
            cout << "Менеджер";
            break;
        case 2:
            cout << "Инженер";
            break;
        case 3:
            cout << "Бухгалтер";
            break;
        case 4:
            cout << "Специалист по кадрам";
            break;
        case 5:
            cout << "Разработчик ПО";
            break;
        case 6:
            cout << "Торговый представитель";
            break;
        case 7:
            cout << "Маркетинговый аналитик";
            break;
        case 8:
            cout << "Генеральный директор";
            break;
        case 9:
            cout << "Технический директор";
            break;
        case 10:
            cout << "Стажер";
            break;
        default:
            cout << "Ошибка";
            break;
        }
    }