#include <iostream>
#include "hash_Table.h"
#include <windows.h>
#include <string>

using namespace std;

void printLine()
{
	cout << "________________________________\n";
}

struct ElementOfTable
{
	int key;
	unsigned char symbol;
	int repeat;
};

int getKey(void* el)
{
	ElementOfTable* element = (ElementOfTable*)el;
	return element->key;
}

char getSymbol(void* el)
{
	ElementOfTable* element = (ElementOfTable*)el;
	return element->symbol;
}

int getRepeat(void* el)
{
	ElementOfTable* element = (ElementOfTable*)el;
	return element->repeat;
}

void addRepeat(void* el)
{
	ElementOfTable* element = (ElementOfTable*)el;
	element->repeat++;
	el = (void*)element;
}

int main()
{
	int size, userInput;
	setlocale(LC_ALL, "Russian");
	cout << "Введите размер хеш-таблицы: ";
	cin >> size;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Table* firstTable = new Table(size, getSymbol, getKey, getRepeat, addRepeat);
	while (true)
	{
		printLine();
		cout << "Меню:\n";
		cout << "1 - ввести предложие\n";
		cout << "2 - показать хеш-таблицу\n";
		cout << "3 - поиск по букве\n";
		cout << "0 - выход из программы\n";
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1:
		{
			string strok;
			cout << "Введите предложение:\n";
			cin.ignore();
			getline(cin, strok);
			for (int i = 0; i < strok.length(); i++)
			{
				ElementOfTable* newElement = new ElementOfTable;
				newElement->symbol = strok[i];
				newElement->key = newElement->symbol;
				newElement->repeat = 1;
				firstTable->addSentence(newElement);
			}
		}
		break;
		case 2:
		{
			firstTable->printTable();
		}
		break;
		case 3:
		{
			unsigned char symbol;
			cout << "Введите букву, информацию о которой хотите узнать: ";
			cin >> symbol;
			firstTable->searchBySymbol(symbol);
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
}
