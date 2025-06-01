#include "Hash_Table.h"
#include <iostream>

bool ht::Table::insertInTable(void* data)
{
	if (hash[getKey(data) % size].head == nullptr)
	{
		element* el = new element;
		el->data = data;
		el->head = el;
		hash[getKey(data) % size].head = el;
	}
	else
	{
		hash[getKey(data) % size].insertInList(data, hash[getKey(data) % size].head);
	}
	return true;
}

void ht::Table::printTable() 
{
	element* data = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (hash[i].head != nullptr)
		{
			std::cout << i + 1 << ": ";
			data = hash[i].head;
			while (data != nullptr)
			{
				std::cout << "| год выпуска:" << getKey(data->data) << " / товар:" << getName(data->data) << " |" << "-->";
				data = hash[i].getNextElement(data);
			}
		}
		std::cout << "NULL\n";
	}
}

void ht::Table::getElementByKey(int year) 
{
	element* data = hash[year % size].head;
	while(data != nullptr && getKey(data->data) != year)
	{ 
		data = hash[year % size].getNextElement(data);
	}
	if (data == nullptr)
	{
		std::cout << "Элемента с заданым годом выпуска нет в таблице\n";
	}
	else
	{
		std::cout << "| год выпуска:" << getKey(data->data) << " / товар:" << getName(data->data) << " |\n";
	}
}

bool ht::Table::deleteElementByKey(int year) 
{
	element* data = hash[year % size].head;
	while (data != nullptr && getKey(data->data) != year) 
	{
		data = hash[year % size].getNextElement(data);
	}
	if (data == nullptr)
	{
		return false;
	}
	else
	{
		hash[year % size].deleteElementFromList(data);
		return true;
	}
}