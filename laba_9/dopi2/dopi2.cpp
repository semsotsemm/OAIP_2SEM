#include <iostream>
#include <windows.h>
#include "function.h"

using namespace std;

void showMenu()
{
	printLine();
	cout << "Меню\n";
	cout << "0 - Выход из программы\n";
	cout << "1 - Показать меню\n";
	cout << "2 - Записать нового студента в список\n";
	cout << "3 - Найти средний бал определенной группы по определенному предемету\n";
	cout << "4 - Определить самого старшего студента\n";
	cout << "5 - Определить самого младшего сиудента\n";
	cout << "6 - Найти лучшего студента с точки зрения успеваемости\n";
	cout << "7 - Вывести отсортированный список всех студентов\n";
	cout << "8 - Считать список из файла\n";
	printLine();
}

int main()
{
	int userInput = 1;
	setlocale(LC_CTYPE, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	showMenu();
	while (userInput != 0)
	{
		cin >> userInput;
		switch (userInput)
		{
		case 0:
			break;
		case 1:
			showMenu();
			break;
		case 2:
			addStudent();
			break;
		case 3:
			calculateAverageScore();
			break;
		case 4:
			findOldest();
			break;
		case 5:
			findYoungest();
			break;
		case 6:
			findTheBestStudent();
			break;
		case 7:
			showList();
			break;
		case 8:
			readList();
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
		cout << "Что дальше?\n";
	}
}