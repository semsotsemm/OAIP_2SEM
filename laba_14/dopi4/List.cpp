#include "List.h"
#include <iostream>

using namespace std;

bool List::insertElement(void* data)
{
	List* ptr = List::head;
	if (ptr != nullptr)
	{
		while (ptr->next != nullptr)
		{
			ptr = ptr->next;
		}
		List* newElement = new List;
		newElement->head = head;
		newElement->value = data;
		newElement->prev = ptr;
		ptr->next = newElement;
	}
	else
	{
		List* newElement = new List;
		newElement->head = head;
		newElement->value = data;
		head = newElement;
	}
	return true;
}

void List::printList() 
{
	List* ptr = head;
	if (ptr != nullptr)
	{
		while (ptr != nullptr)
		{
			cout << getKey(ptr->value) << "-->";
			ptr = ptr->next;
		}
	}
	cout << "NULL";
}

void* List::foundInList(int value) 
{
	List* ptr = head;
	if (ptr != nullptr)
	{
		while (ptr != nullptr && getKey(ptr->value) != value)
		{
			ptr = ptr->next;
		}
	}
	if (getKey(ptr->value) != value)
	{
		int a = -1;
		return (void*)a;
	}
	return ptr->value;
}

bool List::deleteFromList(int value) 
{
	List* ptr = head; 
	if (ptr != nullptr)
	{
		while (ptr != nullptr && getKey(ptr->value) != value)
		{
			ptr = ptr->next;
		}
		if (ptr == head)
		{
			ptr = ptr->next;
			delete(head);
			head = ptr;
			if (ptr != nullptr)
			{
				head->prev = nullptr;
			}
			return true;
		}
		else if(ptr != nullptr)
		{
			ptr->prev->next = ptr->next;
			if (ptr->next != nullptr)
			{
				ptr->next->prev = ptr->prev;
			}
			delete(ptr); 
			return true;
		}
		else
		{
			return false;
		}
	}
}

void List::printListIntoFile() 
{
	List* ptr = head;
	FILE* fdata;
	if (!fopen_s(&fdata, "data.txt", "a+"))
	{
		if (ptr != nullptr)
		{
			while (ptr != nullptr)
			{
				int data = getKey(ptr->value);
				fprintf(fdata, "%d ", data);
				ptr = ptr->next;
			}
		}
		fclose(fdata);
	}
	else
	{
		cout << "Не удалось открыть файл\n";
	}
}