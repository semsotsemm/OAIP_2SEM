#include "Hash_Table.h"
#include <iostream>

using namespace std;

bool Table::pushNewElement(void* newElement) 
{
	return data[getKey(newElement) % size].insertElement(newElement);
}

void Table::printHashTable() 
{
	for (int i = 0; i < size; i++)
	{
		data[i].printList();
		cout << "\n";
	}
}

void* Table::foundElement(int value) 
{
	return data[value % size].foundInList(value);
}
bool Table::deleteElement(int value)
{
	return data[value % size].deleteFromList(value);
}

void Table::pushTableIntoFile() 
{
	for (int i = 0; i < size; i++)
	{
		data[i].printListIntoFile();
	}
}