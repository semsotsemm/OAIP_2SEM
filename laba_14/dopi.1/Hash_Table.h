#include "List.h"

namespace ht
{
	struct Table
	{
		int size;
		element* hash;
		int(*getKey)(void*);
		char* (*getName)(void*);
		Table(int siz, int(*key)(void*), char* (*name)(void*))
		{
			size = siz;
			hash = new element[size];
			getKey = key;
			getName = name;
		}
		bool insertInTable(void* product);
		void printTable();
		void getElementByKey(int year);
		bool deleteElementByKey(int year);
	};
	struct info
	{
		int key;
		char* name;
	};
}