#include "Hash_Chain.h"
#include <iostream>
namespace hashTC
{
	Object create(int size, int(*f)(void*))
	{
		return *(new Object(size, f));
	}

	int Object::hashFunction(void* data) //Метод для определения места где будет хранится данный ключ
	{
		return (FunKey(data) % size); //Получаем позицию в которой хранится наш односвязный список 
	};

	bool Object::insert(void* data) //Метод для добавления нового элемента в хеш-таблицу (возвращает true или false в зависимости от того получилось ли добавить новый элемент)
	{
		return (Hash[hashFunction(data)].insert(data)); //Для элемента хеш-таблицы с индексом hashFunction(data) вызываем метод insert
	};

	bool Object::deleteByData(void* data)
	{
		return (Hash[hashFunction(data)].deleteByData(data)); //Для элемента хеш - таблицы с индексом hashFunction(data) вызываем метод deleteByData
	};

	listx::Element* Object::search(void* data)
	{
		return Hash[hashFunction(data)].search(data); //Для элемента хеш-таблицы с индексом hashFunction(data) вызываем метод search и в него передаем ключ для поимка
	};

	void Object::Scan()
	{
		for (int i = 0; i < size; i++) // пока не дошли до последнего элемента хеш-таблицы выводим состояние каждого элемента 
		{
			Hash[i].scan();
			std::cout << '\n';
		}
	};
}
