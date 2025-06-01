#include "hash_Table.h"
#include <iostream>

using namespace std;

void Table::printList(Element* firstElement)
{
	Element* ptr = firstElement->head;
	while (ptr != nullptr)
	{
		cout << "|" << getSymbol(ptr->data) << ": " << getRepeat(ptr->data) << "|-->";
		ptr = ptr->getNextElement(ptr);
	}
}

void Table::addSentence(void* newElement)
{
	Element* newEl = new Element;
	newEl->data = newElement;
	if (hash[getKey(newElement) % size].data == nullptr)
	{
		newEl->head = newEl;
		hash[getKey(newElement) % size].head = newEl;
		hash[getKey(newElement) % size].data = newEl->data;
	}
	else
	{
		hash[getKey(newElement) % size].addToList(hash[getKey(newElement) % size].head, newEl);
	}
}

void Table::printTable() 
{
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ": ";
		if (hash[i].data != nullptr)
		{
			printList(hash[i].head);
		}
		cout << "NULL\n";
	}
}

void Table::searchBySymbol(int key)
{
	hash[key % size].searchInList(hash[key % size].head, key);
}