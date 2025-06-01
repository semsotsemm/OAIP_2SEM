#include "List.h"

struct Table
{
	int size;
	int (*getKey)(void*);

	List* data;

	Table(int siz, int (*getK)(void*))
	{
		size = siz;
		getKey = getK;

		data = new List[size];

		for (int i = 0; i < size; i++)
		{
			data[i].initialize(getK);
		}
	}

	bool pushNewElement(void* newElement);
	void printHashTable();
	void* foundElement(int value);
	bool deleteElement(int value);
	void pushTableIntoFile();
};