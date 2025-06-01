#include <iostream>

using namespace std;

struct Item
{
	double value;
	Item* next;
};

Item* head, * tail;

void printLine()
{
	cout << "_________________________\n";
}

void showMenu()
{
	printLine();
	cout << "Меню:\n" << "1 - Добавить новое значение в очередь\n";
	cout << "2 - Вывести очередь\n" << "3 - Поместить наибольший элемент на 1 позицию\n";
	cout << "4 - Показать меню\n" << "0 - Выход из программы\n";
	printLine();
}

void addNewEl()
{
	Item* newEl = new Item;
	cout << "Введите новый элемент очереди: ";
	cin >> newEl->value;
	newEl->next = nullptr;
	if (head == nullptr)
	{
		head = tail = newEl;
	}
	else
	{
		tail->next = newEl;
		tail = newEl;
	}
}

void showQueue()
{
	Item* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value << "-->";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

int searchMaxEl()
{
	int max = head->value;
	Item* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->value > max)
		{
			max = ptr->value;
		}
		ptr = ptr->next;
	}
	return max;
}

void deleteElFromQueue(int max)
{
	Item* before, * after;
	before = after = head;
	if (before->value == max)
	{
		head = head->next;
		delete(before);
	}
	else if (after->next != nullptr)
	{
		after = after->next;
		while (after != nullptr)
		{
			if (after->value == max)
			{
				after = after->next;
				break;
			}
			before = after;
			after = after->next;
		}
		before->next = after;
	}
}

void moveQueue()
{
	int max = searchMaxEl();
	deleteElFromQueue(max);
	Item* newValue = new Item;
	newValue->value = max;
	newValue->next = head;
	head = newValue;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int userInput = 1;
	head = nullptr;
	tail = nullptr;
	showMenu();
	while (userInput != 0)
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			addNewEl();
			break;
		case 2:
			showQueue();
			break;
		case 3:
			moveQueue();
			break;
		case 4:
			showMenu();
			break;
		case 0:
			break;
		}
		cout << "Что дальше ?\n";
	}
	return 0;
}