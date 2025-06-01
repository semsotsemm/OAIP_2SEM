#include "List.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Person {
    string name;
    int age;
    bool gender;
};

void printPerson(void* data) {
    Person* p = static_cast<Person*>(data);
    cout << "ФИО: " << p->name
        << "; Год рождения: " << p->age
        << "; Пол: " << (p->gender ? "Ж" : "М")
        << endl;
}

void printLine() { cout << "_________________________\n"; }
void printMenu()
{
    printLine();
    cout << "Меню:\n";
    cout << "0 - Выход из программы\n";
    cout << "1 - Добавить нового гражданина в список\n";
    cout << "2 - Удалить гражданина из списка\n";
    cout << "3 - Поиск по фамилии\n";
    cout << "4 - Вывести список в консоль\n";
    cout << "5 - Подсчитать количество граждан в списке\n";
    cout << "6 - Очистить список\n";
    printLine();
}


int main() {
    setlocale(LC_ALL, "Russian");
    Object L1 = Create();
    int choice;
    string input;

    while (true) {
        printMenu();
        cout << "Введите команду: ";
        if (!(cin >> choice)) break;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0) {
            // очистка памяти
            Element* e = L1.GetFirst();
            while (e) {
                Person* p = static_cast<Person*>(e->Data);
                delete p;
                e = e->Next;
            }
            L1.DeleteList();
            break;
        }

        switch (choice) {
        case 1: {
            Person* newP = new Person;
            cout << "Введите ФИО: ";
            getline(cin, newP->name);
            cout << "Введите год рождения: ";
            cin >> newP->age;
            cout << "Введите пол (0-м, 1-ж): ";
            cin >> newP->gender;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            L1.InsertEnd(newP);
            cout << "Гражданин добавлен.\n";
            break;
        }
        case 2: {
            cout << "Введите ФИО для удаления: ";
            getline(cin, input);
            bool found = false;
            for (Element* e = L1.GetFirst(); e; e = e->Next) {
                Person* p = static_cast<Person*>(e->Data);
                if (p->name == input) {
                    L1.Delete(e);
                    delete p;
                    cout << "Удалён: " << input << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Не найден: " << input << "\n";
            break;
        }
        case 3: {
            cout << "Введите ФИО для поиска: ";
            getline(cin, input);
            bool found = false;
            for (Element* e = L1.GetFirst(); e; e = e->Next) {
                Person* p = static_cast<Person*>(e->Data);
                if (p->name == input) {
                    cout << "Найден: "; printPerson(p);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Не найден: " << input << "\n";
            break;
        }
        case 4:
            cout << "Список граждан:\n";
            L1.PrintList(printPerson);
            break;
        case 5:
            cout << "Количество граждан в списке: " << L1.CountList() << endl;
            break;

        case 6:
            if (L1.DeleteList()) {
                cout << "Список успешно очищен.\n";
            }
            else {
                cout << "Ошибка при очистке списка.\n";
            }
            break;
        default:
            cout << "Ошибка ввода\n";
        }
    }
    return 0;
}