#include "Heap.h"
#include <iostream>

using namespace std;

heap::CMP cmpAAA(void* a1, void* a2)  //������� ���������
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
	return rc; // ���������� 0 ���� �������� �����, 1 ���� A1 > A2 (�������� ����������� ����� � �� ���� ������ ������), -1 ���� A2 > A1 (�������� ������ ������)
#undef A2
#undef A1 
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int k, choice;
	heap::Heap h1 = heap::create(30, cmpAAA); //������� �������� ���� ������������ ������ ������� ����� 30
	for (;;)
	{
		cout << "1 - ����� ���� �� �����" << endl;
		cout << "2 - �������� �������" << endl;
		cout << "3 - ������� ������������ �������" << endl;
		cout << "4 - ������� ����������� �������" << endl;
		cout << "5 - ������� ������� � ������������ ��������" << endl;
		cout << "6 - ���������� 2 ���� � ����" << endl;
		cout << "7 - ��������� ���� ���������� ����������" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� �����" << endl;
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
			cout << "������� ����" << endl;
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
			cout << "������� ����� ���� (���� ��������� 0):\n";
			heap::Heap h2 = heap::create(30, cmpAAA);
			do
			{
				cout << "������� ����: ";
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
			cout << "������� ������ ����: ";
			cin >> size;
			cout << "������� ������������ ��������, ������� ����� ����������� � ����: ";
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
			cout << endl << "������� �������� �������!" << endl;
		}
	} return 0;
}