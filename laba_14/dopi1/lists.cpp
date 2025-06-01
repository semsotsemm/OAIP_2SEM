#include "lists.h"
#include <iostream>

void Element::addToList(Element* firstEl, Element* newEl) 
{
	Element* ptr = firstEl;
	newEl->head = firstEl;
	while (ptr->next != nullptr && getKey(ptr->data) != getKey(newEl->data))
	{
		ptr = ptr->next;
	}
	if (getKey(ptr->data) == getKey(newEl->data))
	{
		addRepeat(ptr->data);
	}
	else if (ptr->next == nullptr)
	{
		newEl->prev = ptr;
		ptr->next = newEl;
	}
}

Element* Element::getNextElement(Element* el)
{
	return el->next;
}

void Element::searchInList(Element* firstElement, int key)
{
	Element* ptr = firstElement;
	while (ptr != nullptr && getKey(ptr->data) != key)
	{
		ptr = ptr->next;
	}
	if (ptr == nullptr)
	{
		std::cout << "���������� ���� ������� ��� � ���-�������\n";
	}
	else
	{
		std::cout << "����: " << getKey(ptr->data) << ", ������: " << getSymbol(ptr->data) << ", ���������� ���������� � �����������: " << getRepeat(ptr->data) << "\n";
	}
}