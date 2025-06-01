#include "function5.h"
#include <iostream>

using namespace std;

void pushNewElement(numbers*& head)
{
	numbers* newEl = new numbers;
	cout << "Введите новое значение: ";
	cin >> newEl->value;
	newEl->next = head;
	head = newEl;
}

void popElement(numbers*& head)
{
	numbers* temp = head;
	if (head != nullptr)
	{
		head = head->next;
		delete(temp);
	}
	else
	{
		cout << "Список пуст";
	}
}

void printList(numbers* head)
{
	numbers* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value << "-->";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

void clear(numbers*& head)
{
	while (head != nullptr)
	{
		popElement(head);
	}
}

void pushListToFile(numbers* head)
{
	FILE* fdata;
	int value;
	numbers* ptr = head;
	if (!fopen_s(&fdata, "data.bin", "ab"))
	{
		while (ptr != nullptr)
		{
			value = ptr->value;
			fwrite(&value, sizeof(int), 1, fdata);
			ptr = ptr->next;
		}
		fclose(fdata);
	}
	else
	{
		cout << "Не удалось открыть файл";
	}
}

void getListFromFile(numbers*& head)
{
	numbers* ptr = new numbers;
	FILE* fdata;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&ptr->value, sizeof(int), 1, fdata))
		{
			ptr->next = head;
			head = ptr;
			ptr = new numbers;
		}
		delete(ptr);
		cout << "Стек успешно получен из файла\n";
		fclose(fdata);
	}
	else
	{
		cout << "Файл не создан\n";
	}
}

bool checkRepeat(int value, numbers* head) 
{
	numbers* ptr = head;
	while (ptr != nullptr)
	{
		if (ptr->value == value)
		{
			return false;
		}
		ptr = ptr->next;
	}
	return true;
}

//3 5 6 7 8 9 6
//3 2 5 8 9 0
//6 7

numbers* formStack(numbers* firstHead, numbers* secondHead, numbers* stack)
{
	numbers*firstPtr = firstHead;
	while (firstPtr != nullptr)
	{
		if (checkRepeat(firstPtr->value, secondHead) && checkRepeat(firstPtr->value, stack))
		{
			numbers* newEl = new numbers;
			newEl->value = firstPtr->value;
			newEl->next = stack;
			stack = newEl;
		}
		firstPtr = firstPtr->next;
	}
	return stack;
}