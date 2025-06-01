#include <iostream>
#include "function7.h"

using namespace std;

void printLine() 
{
	cout << "_____________________________________\n";
}

void printMenu() 
{
	cout << "Меню:\n";
	cout << "1 - Добавить новый элемент в стек\n";
	cout << "2 - Удалить элемент\n";
	cout << "3 - Вывести список в консоль\n";
	cout << "4 - Очистить список\n";
	cout << "5 - Записать список в файл\n";
	cout << "6 - Получить список из файла\n";
	cout << "7 - Удалить элемент больше 100\n";
	cout << "0 - Выход из программы\n";
}

int main()
{
	setlocale(LC_CTYPE,"Russian");
	int userInput;
	numbers* head = nullptr;
	while (true)
	{
		printLine();
		printMenu();
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			pushNewElement(head);
			cout << "Элемент успешно добавлен\n";
			printList(head);
			break;
		case 2:
			popElement(head);
			cout << "Элемент успешно удален\n";
			printList(head);
			break;
		case 3:
			printList(head);
			break;
		case 4:
			clear(head);
			cout << "Список очищен\n";
			break;
		case 5:
			pushListToFile(head);
			cout << "Список записан в файл\n";
			break;
		case 6:
			getListFromFile(head);
			cout << "Список получен из файла\n";
			printList(head);
			break;
		case 7:
			popElementMoreHundred(head);
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
	}
}