#include "List.h"
#include <iostream>

void Element::insertInList(void* newElement, Element* firstElement) 
{
	Element* ptr = firstElement;
	while (ptr->next != nullptr)
	{
		ptr = ptr->next;
	}
	ptr->next = new Element;
	ptr->next->prev = ptr;
	ptr->next->head = head;
	ptr->next->data = newElement;
}

void Element::printList(Element* firstElement) 
{
	Element* ptr = firstElement;
	while (ptr != nullptr)
	{
		std::cout << "|" << getKey(ptr->data) << ": " << getWord(ptr->data) << "|->";
		ptr = ptr->next;
	}
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
		cout << "Данного элемента еще нет в хег-таблице\n";
	}
	else
	{
		std::cout << "__________________________________________________\n";
		std::cout << "Ключ:" << getKey(ptr->data) << ";\nCлово: " << getWord(ptr->data) << ";\n";
		std::cout << "Подсказка к слову: " << getPrompt(ptr->data) << ";\n";
		std::cout << "__________________________________________________\n";
	}
}