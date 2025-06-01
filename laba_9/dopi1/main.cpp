#include "List.h"
#include <iostream>

using namespace std;

struct Person
{
	char name[20];
	int age;
	Person* next;
};

void print(void* b)       //Функция используется при выводе 
{
	if (b == NULL)
	{
		cout << "Список пуст\n";
		return;
	}
	Person* a = (Person*)b;
	cout << a->name << "  " << a->age << endl;
}

void printLine() 
{
	cout << "______________________________\n";
}

void showMenu() 
{
	printLine();
	cout << "Меню:\n";
	cout << "1 - Удалить элемент из списка \n";
	cout << "2 - Очистить список\n";
	cout << "3 - Вывести список\n";
	cout << "4 - Показать меню\n";
	cout << "5 - Поиск элемента\n";
	cout << "6 - Посчитать количество элементов\n";
	cout << "7 - Выход из программы\n";
	printLine();
}

int main()
{
	int userInput = 0;
	setlocale(LC_ALL, "Russian");
	Person a1 = { "Петров", 20 };
	Person a2 = { "Сидоров", 25 };
	Person a3 = { "Гончаров", 47 };
	bool rc;
	Object L1 = Create();   // создание списка с именем L1
	L1.Insert(&a1);
	L1.Insert(&a2);
	L1.Insert(&a3);
	L1.PrintList(print);
	showMenu();
	while (userInput != 7)
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			rc = L1.Delete(&a2);
			if (rc == true)
			{
				cout << "Элемент удален" << endl;
			}
			else
			{
				cout << "Элемент не найден" << endl;
			}
			cout << "Список:" << endl;
			L1.PrintList(print);
			break;
		case 2: 
			if (L1.DeleteList())
			{
				cout << "Список успешно очищен\n";
			}
			else
			{
				cout << "Ошибка очистки списка\n";
			}
			break;
		case 3: 
			L1.PrintList(print);
			break;
		case 4: 
			showMenu();
			break;
		case 5:
		{
			Element* e = L1.Search(&a3);
			Person* aa = (Person*)e->Data;
			cout << "Найден элемент= " << aa->name << endl;
			break;
		}
		case 6:
			cout << "Количество элементов в списке: " << L1.CountList() << endl;
			break;
		case 7:
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
		cout << "Что дальше?\n";
	}
	return 0;
}
