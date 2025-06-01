#include "Heap.h"
#include <iostream>

using namespace std;

heap::CMP cmpAAA(void* a1, void* a2)  //‘ункци€ сравнени€
{
#define A1 ((AAA*)a1)  
#define A2 ((AAA*)a2)
	heap::CMP
		rc = heap::EQUAL;
	if (A1->x > A2->x)
	{
		rc = heap::GREAT;
	}
	else
	{
		if (A2->x > A1->x)
		{
			rc = heap::LESS;
		}
	}
	return rc; // возвращает 0 если элементы равны, 1 если A1 > A2 (элементы расположены верно и не надо ничего мен€ть), -1 если A2 > A1 (элементы требую замену)
#undef A2
#undef A1 
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int k, choice;
	heap::Heap h1 = heap::create(30, cmpAAA); //создаем бинарную кучу максимальный размер которой будет 30
	for (;;)
	{
		cout << "1 - вывод кучи на экран" << endl;
		cout << "2 - добавить элемент" << endl;
		cout << "3 - удалить максимальный элемент" << endl;
		cout << "4 - удалить минимальный элемент" << endl;
		cout << "5 - удалить элемент с определенным индексом" << endl;
		cout << "6 - объединить 2 кучи в одну" << endl;
		cout << "7 - заполнить кучу случайными значени€ми" << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			exit(0);
		case 1:
			h1.scan(0);
			break;
		case 2:
		{
			AAA* a = new AAA;
			cout << "введите ключ" << endl;
			cin >> k;
			a->x = k;
			h1.insert(a);
		}
		break;
		case 3:
			h1.extractMax();
			break;
		case 4:
			h1.extractMin();
			break;
		case 5:
			h1.extractI();
			break;
		case 6:
		{
			int userInput = 0;
			cout << "¬ведите новую кучу (ввод закончите 0):\n";
			heap::Heap h2 = heap::create(30, cmpAAA);
			do
			{
				cout << "¬ведите ключ: ";
				cin >> userInput;
				if (userInput != 0)
				{
					AAA* a = new AAA;
					a->x = userInput;
					h2.insert(a);
				}
			} while (userInput);
			h1.unionHeap(h2);
			break;
		}
		case 7:
		{
			int size, max;
			cout << "¬ведите размер кучи: ";
			cin >> size;
			cout << "¬ведите максимальный значение, которое может содержатьс€ в куче: ";
			cin >> max;
			for (int i = 0; i < size; i++)
			{
				AAA* a = new AAA;
				int k = rand() % max + 1;
				a->x = k;
				h1.insert(a);
			}
			break;
		}
		default:
			cout << endl << "¬ведена неверна€ команда!" << endl;
		}
	} return 0;
}