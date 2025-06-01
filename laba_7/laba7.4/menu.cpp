#include <iostream>
#include "function.h"

using namespace std;

void printline()
{
	cout << "____________________________________\n";
}

void showmenu()
{
	printline();
	cout << "Меню:\n" << "1 - Добавления нового значения в стек\n";
	cout << "2 - Удаление элемента из стека\n" << "3 - Запись стека в файл\n";
	cout << "4 - Чтение стека из файла\n" << "5 - Очистка стека\n";
	cout << "6 - Построить stack1 и stack2\n" << "7 - Вывод стека\n";
	cout << "8 - Вывод меню\n" << "0 - Выход из программы\n";
	printline();
}

int main()
{
	int userInput;
	stack* first = new stack;
	first = nullptr;
	setlocale(LC_CTYPE, "Russian");
	showmenu();
	do
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			inputToStack(first);
			showList(first);
			break;
		case 2:
			if (!isStackEmpty(first))
			{
				delFromStack(first);
			}
			else
			{
				cout << "Стек пуст\n";
			}
			break;
		case 3:
			inputStackToFile(first);
			clear(first);             //При записи в файл стек записывается в обратном порядке из-за свойства FILO 
			readFromFile(first);      //Для того чтобы это исправить запишем его 2 раза (2-ая инверсия)
			remove("data.bin");
			inputStackToFile(first);
			cout << "Стек успешно записан в файл data.bin\n";
			break;
		case 4:
			readFromFile(first);
			cout << "Данные из файла успешно считаны и записаны в стек: \n";
			showList(first);
			break;
		case 5:
			clear(first);
			cout << "Стек успешно очищен\n";
			break;
		case 6:
			buildNewStack(first);
			break;
		case 7:
			showList(first);
			break;
		case 8:
			showmenu();
			break;
		case 0:
			break;
		default:
			cout << "Ошибка ввода";
			break;
		}
		cout << "Что дальше?\n";
	} while (userInput != 0);
}