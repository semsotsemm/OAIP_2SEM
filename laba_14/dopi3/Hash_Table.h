#include "List.h"

using namespace std;

struct Table
{
	int size;
	Element* hash;
	int (*getKey)(void*);
	string (*getWord)(void*);
	string (*getPrompt)(void*);
	Table(int siz, int (*getK)(void*), string (*getW)(void*), string (*getP)(void*))
	{
		getKey = getK;
		getWord = getW;
		getPrompt = getP;
		size = siz;
		hash = new Element[siz];
		for (int i = 0; i < size; i++)
		{
			hash[i].initialize(getK, getW, getP);
		}
	}

	void insertInTable(void* newElement);
	void printTable();
	void searchWordByKey(int key);

	~Table() 
	{
		delete[]hash;
	}
};