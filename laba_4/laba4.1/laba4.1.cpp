#include <iostream>
#include <windows.h>

using namespace std;

struct Worker
{
	char lastName[30];
	char name[30];
	char fatherName[30];
	char position[5];
	int year;
};

int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	const int size = 3;
	const int currentYear = 2025;
	int  b, counter = 0;
	Worker a[size];
	for (int i = 0; i < size; i++)
	{
		cout << "Введите фамилию " << i + 1 << "-ого работника: ";
		cin >> a[i].lastName;
		cout << "Введите имя " << i + 1 << "-ого работника: ";
		cin >> a[i].name;
		cout << "Введите отчество " << i + 1 << "-ого работника: ";
		cin >> a[i].fatherName;
		cout << endl << "Должность: ";
		cin >> a[i].position;
		cout << endl << "Год поступления на работу: ";
		cin >> a[i].year;
	}
	cout << endl << "Введите стаж работы ";
	cin >> b;
	for (int i = 0; i < size; i++)
	{
		if (b < currentYear - a[i].year)
		{
			cout << endl << "Фио сотрдуника, стаж работы которого более " << b << " лет: " << a[i].lastName << " " << a[i].name << " " << a[i].fatherName;
			counter++;
		}
		else
			if (i == size - 1 && counter > 0)
				cout << "Работников с более высоким стажем нет.";
	}
	return 0;
}