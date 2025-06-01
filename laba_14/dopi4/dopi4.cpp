#include <iostream>
#include <string>
#include "Hash_Table.h"

using namespace std;

struct Element
{
	int value;
};

void printLine();

void printMenu();

bool convertToNum(string line, int& num);

int getKey(void* data);

int main()
{
	setlocale(LC_CTYPE, "Russian");
	string line;
	int userInput;
	cout << "Введите размер хеш-таблицы: ";
	getline(cin, line);

	if (convertToNum(line, userInput))
	{
		printMenu();
		Table* newTable = new Table(userInput, getKey);
		while (true)
		{
			getline(cin, line);
			if (convertToNum(line, userInput))
			{
				switch (userInput)
				{
				case 1:
					printMenu();
					break;
				case 2:
					newTable->printHashTable();
					break;
				case 3:
				{
					Element* newElement = new Element;
					cout << "Введите значение нового элемента: ";
					cin >> newElement->value;
					cin.ignore();
					newTable->pushNewElement(newElement);
					cout << "Элемент успешно записан:\n";
					newTable->printHashTable();
				}
					break;
				case 4:
				{
					int value;
					cout << "Введите значение элемента, которого хотите найти:  ";
					cin >> value;
					cin.ignore();
					void* element = newTable->foundElement(value);
					if (element != nullptr)
					{
						cout << "Элемент найден: " << getKey(element) << endl;
					}
					else
					{
						cout << "Данного элемента нет в хеш-таблице\n";
					}
				}
					break;
				case 5:
				{
					int temp;
					cout << "Введите значение элемента, который хотите удалить: ";
					cin >> temp;
					cin.ignore();
					if (newTable->deleteElement(temp))
					{
						cout << "Элемент со значением "<< temp <<" успешно удален:\n";
						newTable->printHashTable();
					}
					else
					{
						cout << "Данного элемента нет в хеш-таблице\n";
					}
					break;
				}
				case 6: 
				{
					FILE* fdata;
					if (!fopen_s(&fdata, "data.txt", "r"))
					{
						Element* newElement = new Element;
						while (fscanf_s(fdata, "%d", &newElement->value) == 1)	
						{
							newTable->pushNewElement(newElement);
							newElement = new Element;
						}
						fclose(fdata);
						cout << "Информация успешно получена из файла:\n";
						newTable->printHashTable();
					}
					else
					{
						cout << "Ошибка: файл не создан\n";
					}
				}
				break;
				case 7:
					newTable->pushTableIntoFile();
					cout << "Информация записана в файл\n";
					break;
				case 0:
					exit(0);
					break;
				default:
					cout << "Ошибка ввода\n";
					break;
				}
			}
			else
			{
				cout << "Ошибка ввода\n";
			}
		}
	}
	else
	{
		cout << "Ошибка ввода\n";
	}
	return 0;
}

void printLine()
{
	cout << "_______________________________________\n";
}

bool convertToNum(string line, int& num) 
{
	int repeat = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			repeat++;
		}
	}
	if (repeat == line.length())
	{
		num = stoi(line);
		return true;
	}	
	return false;
}

void printMenu() 
{
	printLine();
	cout << "Меню:\n";
	cout << "1 - Вывести меню\n";
	cout << "2 - Вывести хеш-таблицу\n";
	cout << "3 - Добавить новый элемент в хеш-таблицу\n";
	cout << "4 - Поиск элемента хеш-таблицы\n";
	cout << "5 - Удалить элемент из хеш-таблицы\n";
	cout << "6 - Получить хеш-таблицу из файла\n";
	cout << "7 - Записать хеш-таблицу в файл\n";
	cout << "0 - Выход из программы\n";
	printLine();
}

int getKey(void* data)
{
	Element* temp = (Element*)data;
	return temp->value;
}