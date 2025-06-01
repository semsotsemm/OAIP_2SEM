#include "List.h";
#include <iostream>


void element::insertInList(void* data,element* firstel)
{
	element* el = firstel;
		while (el->next != nullptr)
		{
			el = el->next;
		}
		element* ptr = new element;
		ptr->head = firstel;
		ptr->data = data;
		ptr->prev = el;
		el->next = ptr;
}

element* element::getNextElement(element* ptrEl)
{
	return ptrEl->next;
}
// 7 4 6 4 3 2
void element::deleteElementFromList(element* ptrEl) 
{
	element* temp;
	if (ptrEl->next == nullptr) // последниий элемент
	{
		temp = ptrEl;
		ptrEl->prev->next = nullptr;
	}
	else if (ptrEl->prev == nullptr) //первый элемент
	{
		temp = ptrEl;
		head = ptrEl->next;
		ptrEl->next->prev = nullptr;
	}
	else
	{
		temp = ptrEl;
		ptrEl->prev->next = ptrEl->next;
		ptrEl->next->prev = ptrEl->prev;
	}
	delete(temp);
}