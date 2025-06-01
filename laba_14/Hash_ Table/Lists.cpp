#include "Lists.h"
#include <iostream>

struct AAA        //������� �������
{
	int key;
	char* mas;
};

namespace listx
{
	bool Object::insert(void* data)
	{
		bool rc = NULL;
		if (head == NULL) // ���� head == NULL (�� ����� �� ���� ��������� � ����� �� �������� �� ������� )  
			head = new Element(NULL, data, head); // ����������� ��� Element ��������� ������ �� ���������� (NULL), ���������(head), �������� ���-�������, � ����� ������
		else
			head = (head->prev = new Element(NULL, data, head)); //���������� ��������� Element ��������� ���������
		return rc;
	}
	//-------------------------------
	Element* Object::search(void* data) //���� ������� � ������ �� �����
	{
		Element* rc = head; // rc - ��������� �� ������ ������� � ����������� ������ 
		while ((rc != NULL) && ((((AAA*)rc->data)->key) != ((AAA*)data)->key)) // ���� �� ������ �� ����� ������� ��� ���� �� ������� ������� � ����� �� ������ ��� �������
			rc = rc->next; // ��������� � ���������� 
		return rc;
	}
	//-------------------------------
	bool Object::deleteByElement(Element* e)
	{
		bool rc = NULL; 
		if (rc = (e != NULL)) // ��������� ����� �� �� ������� ��� ������ ����� �� ����� ������ � � rc ������������� ������� ������� ����� ������� 
		{
			if (e->next != NULL) // ���� ��������� ������� �� ����� NULL (���� �� ����� ������)
				e->next->prev = e->prev; // � ���� prev ���������� �������� ������������� ���������� �������
			if (e->prev != NULL) // ���� ���������� ������� �� ����� NULL (���� �� ������ ������)
				e->prev->next = e->next; // � ���� next ����������� �������� ������������� ��������� �������
			else // ���� ������� ��������� � ������ ������
				head = e->next; // � head ������������� ��������� ������� 
			delete e; // ������� ������� 
		}
		std::cout << "������� ������" << std::endl;
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
		listx::Element* e = this->getFirst(); // � ���������� e ����������� ������ �� ������ ������� 
		while (e != NULL) // ���� e �� ����� ��������� �� nullptr (����� �������)
		{
			std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / "; //������� ���� � ������ �������� �������� 
			e = e->getNext(); // � � �������� ��������� �� ��������� �������
		};
	}
}
