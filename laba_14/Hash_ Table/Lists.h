#pragma once              //Заголовочный файл Lists.h
#define LISTNIL (Element*)-1
namespace listx
{
	struct Element
	{
		Element* prev;
		Element* next;
		void* data;
		Element(Element* pr, void* dat, Element* nt) // конструктор для element в поле prev присваиваем ссылку на предыдущий Element в data данные которые хранит определенный ключ в next ссвлку на слудующий элемент хеш-таблицы 
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
			head = NIL; //Конструктор для Object присваивает началу очереди nullptr 
		};
		Element* getFirst()
		{
			return head; // возвращаем ссылку на 1 элемент очереди
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
