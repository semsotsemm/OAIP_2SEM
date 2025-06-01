#include "Hash_Table.h"
#include <iostream>

void Table::insertInTable(void* newElement)
{
	if (hash[getKey(newElement) % size].head == nullptr)
	{
		hash[getKey(newElement) % size].head = new Element;
		hash[getKey(newElement) % size].head = hash[getKey(newElement) % size].head;
		hash[getKey(newElement) % size].head->data = newElement;
	}
	else
	{
		hash[getKey(newElement) % size].insertInList(newElement, hash[getKey(newElement) % size].head);
	}
}

void Table::printTable() 
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1 << ": ";
		if (hash[i].head != nullptr)
		{
			hash[i].printList(hash[i].head);
		}
		std::cout << "NULL\n";
	}
}

void Table::searchWordByKey(int key) 
{
	if (hash[key % size].head == nullptr)
	{
		cout << "Данного слова еще нет в хеш-таблице\n";
	}
	else 
	{
		hash[key % size].searchInList(hash[key % size].head, key);
	}
}