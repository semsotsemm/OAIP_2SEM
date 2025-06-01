#include "function.h"
#include <iostream>

using namespace std;

void pushNewElement(stack*& head) 
{
	stack* newElement = new stack,* ptr = head;
	cout << "Введите новый элемент: ";
	cin >> newElement->value;
	newElement->next = nullptr;
	newElement->prev = nullptr;
	if (head == nullptr)
	{
		head = newElement;
	}
	else
	{
		newElement->next = head;
		head->prev = newElement;
		head = newElement;
	}
}

void popElement(stack*& head) 
{
	stack* temp;
	if (head == nullptr)
	{
		cout << "Список пуст\n";
	}
	else
	{
		temp = head;
		head = head->next;
		if (head != nullptr)
		{
			head->prev = nullptr;
		}
		delete(temp);
	}
}

void printStack(stack* head)
{
	stack* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value <<"-->";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

void clear(stack*& head)
{
	while (head != nullptr)
	{
		popElement(head);
	}
}

void popPositiveElement(stack*& head)
{
	stack* ptr = head;
	while (ptr != nullptr && ptr->value < 0)
	{
		ptr = ptr->next;
	}
	if (ptr == nullptr && head == nullptr)
	{
		cout << "Список пуст\n";
	}
	else if (ptr == nullptr)
	{
		cout << "Все элементы списка отрицательные\n";
	}
	else
	{
		ptr->prev->next = ptr->next;
		ptr->next->prev = ptr->prev;
		delete(ptr);
	}
}

void pushStackToFile(stack* head)
{
	FILE* fdata;
	stack* ptr = head;
	int value;
	if (!fopen_s(&fdata, "data.bin", "ab"))
	{
		while (ptr != nullptr)
		{
			value = ptr->value;
			fwrite(&value, sizeof(int), 1, fdata);
			ptr = ptr->next;
		}
		fclose(fdata);
		cout << "Список успешно записан в файл data.bin\n";
	}
	else
	{
		cout << "Не удалось открыть файл для записи\n";
	}
}

void getStackFromFile(stack*& head)
{
	stack * ptr = new stack;
	FILE* fdata;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&ptr->value, sizeof(int), 1, fdata))
		{
			ptr->next = head;
			head = ptr;
			ptr = new stack;
		}
		cout << "Стек успешно получен из файла\n";
		fclose(fdata);
	}
	else 
	{
		cout << "Файл не создан\n";
	}
}