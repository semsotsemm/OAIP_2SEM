#include <iostream>

using namespace std;

struct list
{
	int value;
	list* next;
};

void printline()
{
	cout << "_____________________________________________\n";
}

void showmenu()
{
	printline();
	cout << "Меню:\n" << "1 - Добавить новый элемент в список\n";
	cout << "2 - Вывод списка\n" << "3 - Удалить элемент из списка\n";
	cout << "4 - Поиск элемента\n" << "5 - Записать список в файл\n";
	cout << "6 - Считать список из файла\n" << "7 - Сумма положительных элементов списка\n";
	cout << "8 - Вывод меню\n" << "0 - Выход из программы\n";
	printline();
}

void inputel(list*& first)
{
	int el;
	list* newel = new list;
	cout << "Введите элемент который хотите добавить: ";
	cin >> el;
	newel->value = el;
	newel->next = first;
	first = newel;
}

void showlist(list* first)
{
	if (first == nullptr)
	{
		cout << "Список пуст\n";
	}
	while (first != nullptr)
	{
		cout << first->value << "-->";
		first = first->next;
	}
	cout << "NULL" << endl;
}

bool delel(list*& first)
{
	bool isElDel = false;
	list* temp = first;
	list* previous = first, * following = first;
	int el;
	cout << "Введите значение элемента который хотите удалить: ";
	cin >> el;
	if (first->value == el)
	{
		first = first->next;
		delete(temp);
	}
	else
	{
		while (following->value != el && following != NULL)
		{
			previous = following;
			following = following->next;
		}
		if (following == NULL)
		{
			cout << "Заданного значения нет в списке\n";
		}
		else
		{
			temp = following;
			previous->next = following->next;
			delete(temp);
			isElDel = true;
			return isElDel;
		}
	}
	return isElDel;
}

void searchel(list* first)
{
	int i = 1;
	int searchnum;
	bool resultOfSearch = false;
	cout << "Введите число которое хотите найти в списке: ";
	cin >> searchnum;
	while (first != nullptr)
	{
		if (first->value == searchnum)
		{
			cout << "Ваше число находится на " << i << " позиции с конца, ";
			if (searchnum > 0)
			{
				cout << "и является положительным\n";
			}
			else if (searchnum < 0)
			{
				cout << "и является отрицательным\n";
			}
			else
			{
				cout << "И является нулем\n";
			}
			resultOfSearch = true;
		}
		i++;
		first = first->next;
	}
	if (!resultOfSearch)
	{
		cout << "Заданного чиcла нет в списке\n";
	}
}

void fileinput(list* first)
{
	FILE* fdata;
	int writedata;
	if (!fopen_s(&fdata, "data.bin", "ab"))
	{
		while (first != nullptr)
		{
			writedata = first->value;
			fwrite(&writedata, sizeof(int), 1, fdata);
			first = first->next;
		}
		fclose(fdata);
	}
	else
	{
		cout << "Не удалось открыть файл для записи\n";
	}
}

void outputFromFile(list*& first,int el) 
{
	list* newel = new list;
	newel->value = el;
	newel->next = first;
	first = newel;
}

void fileoutput(list*& first)
{
	FILE* fdata;
	int el;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&el, sizeof(int), 1, fdata))
		{
			outputFromFile(first, el);
		}
		fclose(fdata);
	}
}

bool sumpositive(list* first, int& sum) 
{
	while (first != nullptr)
	{
		if (first->value > 0)
		{
			sum += first->value;
		}
		first = first->next;
	}
	if (sum != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	int userInput;
	list* first = nullptr;
	setlocale(LC_CTYPE, "Russian");
	showmenu();
	do
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			inputel(first);
			cout << "Элемент успешно добавлен:\n";
			showlist(first);
			break;
		case 2:
			showlist(first);
			break;
		case 3:
			if (delel(first))
			{
				cout << "Элемент успешно удален:\n";
				showlist(first);
			}
			else
			{
				cout << "Ошибка удаления элемента из списка!\n";
			}
			break;
		case 4:
			searchel(first);
			break;
		case 5:
			fileinput(first);
			break;
		case 6:
			fileoutput(first);  
			showlist(first);
			break;
		case 7:
		{
			int sum = 0;
			if (sumpositive(first, sum))
			{
				cout << "Сумма положительных элементов = " << sum << endl;
			}
			else
			{
				cout << "В списке нет положительных элементов\n";
			}
			break;
		}
		case 8:
			showmenu();
			break;
		case 0:
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
		cout << "Что дальше?\n";
	} while (userInput != 0);
}