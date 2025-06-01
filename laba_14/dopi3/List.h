#include <iostream>

using namespace std;

struct Element
{
	Element* next;
	Element* prev;
	Element* head;
	void* data;
	int (*getKey)(void*);
	string (*getWord)(void*);
	string (*getPrompt)(void*);

	Element()
	{
		next = nullptr;
		prev = nullptr;
		head = nullptr;
		data = nullptr;
	}

	void insertInList(void* newElement, Element* firstElement);
	void printList(Element* firstElement);
	void searchInList(Element* firstElement, int key);

	void initialize(int (*getK)(void*), string(*getW)(void*), string(*getP)(void*))
	{
		getKey = getK;
		getWord = getW;
		getPrompt = getP;
	}
};