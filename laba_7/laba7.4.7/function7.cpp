#include "function7.h"
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
		cout <<ptr->value<< "-->";
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

void popElementMoreHundred(numbers*& head) 
{
	numbers* ptr = head,* prev = nullptr;
	if (head != nullptr)
	{
		while (ptr != nullptr && ptr->value < 100)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		if (prev == nullptr || ptr->value > 100)
		{
			prev = head;
			head = head->next;
			delete(prev);
		}
		else if (ptr->value > 100)
		{
			prev->next = ptr->next;
			delete(ptr);
			cout << "Элемент успешно удален\n";
			printList(head);
		}
		else
		{
			cout << "Элемента больше 100 нет в списке\n";
		}
	}
	else
	{
		cout << "Список пуст\n";
	}
}