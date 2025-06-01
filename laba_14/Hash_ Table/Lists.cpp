#include "Lists.h"
#include <iostream>

struct AAA        //элемент таблицы
{
	int key;
	char* mas;
};

namespace listx
{
	bool Object::insert(void* data)
	{
		bool rc = NULL;
		if (head == NULL) // если head == NULL (до этого не было элементов с таким же остатком от деления )  
			head = new Element(NULL, data, head); // конструктор для Element принимает ссылку на предыдущий (NULL), слудующий(head), элементы хеш-таблицы, а также данные
		else
			head = (head->prev = new Element(NULL, data, head)); //Записывает введенный Element следующим элементом
		return rc;
	}
	//-------------------------------
	Element* Object::search(void* data) //ищет элемент в списке по ключу
	{
		Element* rc = head; // rc - указатель на первый элемент в односвязном списке 
		while ((rc != NULL) && ((((AAA*)rc->data)->key) != ((AAA*)data)->key)) // пока не дойдем до конца очереди или пока не встетим элемент с таким же ключом как вводили
			rc = rc->next; // переходим к следующему 
		return rc;
	}
	//-------------------------------
	bool Object::deleteByElement(Element* e)
	{
		bool rc = NULL; 
		if (rc = (e != NULL)) // проверяем нашли ли мы элемент или просто дошли до конца списка и в rc устанавливаем элемент который будем удалять 
		{
			if (e->next != NULL) // если следующий элемент не равен NULL (если не конец списка)
				e->next->prev = e->prev; // в поле prev следующего элемента устанавливаем предыдущий элемент
			if (e->prev != NULL) // если предыдущий элемент не равен NULL (если не начало списка)
				e->prev->next = e->next; // в поле next предыдущего элемента устанавливаем слелующий элемент
			else // если элемент находится в начале списка
				head = e->next; // в head устанавливаем следующий элемент 
			delete e; // удаляем элемент 
		}
		std::cout << "Элемент удален" << std::endl;
		return rc;
	}
	//-------------------------------
	bool Object::deleteByData(void* data)
	{
		return deleteByElement(search(data)); 
	}
	//-------------------------------
	Element* Object::getLast()
	{
		listx::Element* e = this->getFirst(), * rc = this->getFirst();
		while (e != NULL)
		{
			rc = e;
			e = e->getNext();
		};
		return rc;
	}

	Object create()
	{
		return *(new Object());
	};
	//-------------------------------
	void Object::scan()
	{
		listx::Element* e = this->getFirst(); // в переменную e присваиваем ссылку на начало очереди 
		while (e != NULL) // пока e не будет указывать на nullptr (конец очереди)
		{
			std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / "; //выводим ключ и данные текущего элемента 
			e = e->getNext(); // в е помещаем указатель на следующий элемент
		};
	}
}
