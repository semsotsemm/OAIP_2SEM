#pragma once              //������������ ���� Lists.h
#define LISTNIL (Element*)-1
namespace listx
{
	struct Element
	{
		Element* prev;
		Element* next;
		void* data;
		Element(Element* pr, void* dat, Element* nt) // ����������� ��� element � ���� prev ����������� ������ �� ���������� Element � data ������ ������� ������ ������������ ���� � next ������ �� ��������� ������� ���-������� 
		{
			prev = pr;
			data = dat;
			next = nt;
		}
		Element* getNext()
		{
			return next;
		};
		Element* getPrev()
		{
			return prev;
		};
	};
	static Element* NIL = nullptr;
	struct Object
	{
		Element* head;
		Object()
		{
			head = NIL; //����������� ��� Object ����������� ������ ������� nullptr 
		};
		Element* getFirst()
		{
			return head; // ���������� ������ �� 1 ������� �������
		};
		Element* getLast();
		Element* search(void* data);
		bool insert(void* data);
		bool deleteByElement(Element* e);
		bool deleteByData(void* data);
		void scan();
	};
	Object create();
}
#undef LISTNIL 
