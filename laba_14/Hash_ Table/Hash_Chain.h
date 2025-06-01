#pragma once            //Заголовочный файл Hash_Chain.h
#include "Lists.h"
namespace hashTC
{
	struct Object
	{
		int size;
		int(*FunKey)(void*);
		listx::Object* Hash;
		Object(int siz, int(*f)(void*)) //Конструктор структуры Object создает хеш-таблицу размера size и с ключом f (f ссылается на область памяти которая может хранить любой тип данных) 
		{
			size = siz;
			FunKey = f;
			Hash = new listx::Object[size]; // выделяем память под size элементов таблицы
		};
		int hashFunction(void* data);
		bool insert(void* data);
		listx::Element* search(void* data);
		bool deleteByData(void* data);
		void Scan();
	};
	Object create(int size, int(*f)(void*)); //метод create принимает размер хеш-таблицы и указатель для хранения данных
}
