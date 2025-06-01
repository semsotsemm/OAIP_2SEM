#include <iostream>
#include "function.h"

using namespace std;

void printLine()
{
	cout << "__________________________________________________\n";
}

void printMenu()
{
	cout << "Меню\n";
	cout << "1 - Добавить новый элемент\n";
	cout << "2 - Удалить элемент\n";
	cout << "3 - Вывести стек в консоль\n";
	cout << "4 - Очистить стек\n";
	cout << "5 - Удалить первый положительный элемент\n";
	cout << "6 - Сохранить в файл\n";
	cout << "7 - Получить стек из файла\n";
	cout << "0 - Выход из программы\n";
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	stack* head = nullptr;
	int userInput;
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
			cout << "Ваш стек: ";
			printStack(head);
			break;
		case 2:
			popElement(head);
			cout << "Элемент успешно удален\n";
			cout << "Ваш стек: ";
			printStack(head);
			break;
		case 3:
			printStack(head);
			break;
		case 4:
			clear(head);
			cout << "Стек успешно очищен\n";
			break;
		case 5:
			popPositiveElement(head);
			cout << "Первый положительный элемент успешно удален\n";
			cout << "Ваш стек: ";
			printStack(head);
			break;
		case 6:
			pushStackToFile(head);
			cout << "Стек успешно записан в файл\n";
			break;
		case 7:
			getStackFromFile(head);
			cout << "Ваш стек: ";
			printStack(head);
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
	}
}