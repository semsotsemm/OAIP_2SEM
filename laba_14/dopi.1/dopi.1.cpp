#include <iostream>
#include "Hash_Table.h"

using namespace std;

void printLine()
{
	cout << "_______________________________________\n";
}

struct productInformation
{
	int key;
	char* nameOfProduct;
};

int getKey(void* info)
{
	productInformation* data = (productInformation*)info;
	return data->key;
}

char* getName(void* info)
{
	productInformation* data = (productInformation*)info;
	return data->nameOfProduct;
}


int main()
{
	int userInput, size;
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите размер хеш-таблицы: ";
	cin >> size;
	ht::Table firstTable(size, getKey, getName);
	while (true)
	{
		printLine();
		cout << "Меню:\n";
		cout << "1 - Добавить новый элемент в хеш-таблицу\n";
		cout << "2 - Вывести хеш-таблицу\n";
		cout << "3 - Удаление элемента по ключу\n"; // true/false
		cout << "4 - Поиск элемента по ключу\n";
		cout << "0 - Выход из программы\n";
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1:
		{
			productInformation* product = new productInformation;
			char* title = new char[20];
			cout << "Введите название товара: ";
			cin >> title;
			product->nameOfProduct = title;
			cout << "Введите год выпуска товара: ";
			cin >> product->key;
			if (firstTable.insertInTable(product))
			{
				cout << "Элемент успешно добавлен\n";
			}
			else 
			{
				cout << "Не удалось добавить элемент\n";
			}
		}
		break;
		case 2:
			firstTable.printTable();
			break;
		case 3:
			cout << "Введите ключ: ";
			int year;
			cin >> year;
			if (firstTable.deleteElementByKey(year))
			{
				cout << "Элемент успешно удален\n";
			}
			else 
			{
				cout << "Элемента с данным ключом нет в хеш-таблице\n";
			}
			break;
		case 4:
		{
			int year;
			cout << "Введите ключ: ";
			cin >> year;
			firstTable.getElementByKey(year);
		}
		break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
	}
	return 0;
}