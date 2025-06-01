#include "Hash_Chain.h"
#include <iostream>
using namespace std;
struct AAA
{
	int key;
	char* mas;
	AAA(int k, char* z) // ����������� ��� AAA ��� ������� ����� �������� ���-�������, ��� ������� ������������ (�������� � ����)
	{
		key = k;
		mas = z;
	}
	AAA() // ������������ ��� AAA � ������ ���� ������ �� �������� ��� ������������� 
	{
		key = 0; // ���� = 0
		mas = nullptr; //��������� �� ������ ������ �� ���������
	}
};
int hf(void* d)
{
	AAA* f = (AAA*)d; //����������� void* � ��������� ��� ��� ����������� ���������� � ����� � ������
	return f->key;
}
//-------------------------------
void AAA_print(listx::Element* e)
{
	std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / "; // ������� ������������ ������� � ������� 
}
//-------------------------------
int main()
{
	setlocale(LC_ALL, "rus");
	int current_size = 7;
	cout << "������� ������ ���-�������" << endl;
	cin >> current_size; //������ ������ ������� � ���������� 
	hashTC::Object H = hashTC::create(current_size, hf); //��� ������ ������ create ������� ���-�������
	int choice;
	int k;
	for (;;)
	{
		cout << "1 - ����� ���-�������" << endl;
		cout << "2 - ���������� ��������" << endl;
		cout << "3 - �������� ��������" << endl;
		cout << "4 - ����� ��������" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 2: {
			AAA* a = new AAA;
			char* str = new char[20];
			cout << "������� ����" << endl;
			cin >> k;
			a->key = k;
			cout << "������� ������" << endl;
			cin >> str;
			a->mas = str;
			H.insert(a); // ����� Object ��� ������� ����� ��������� 
		}
			  break;
		case 1: 
			H.Scan();// ����� Object ��� ������ ���-�������
			break;
		case 3: {
			AAA* b = new AAA;
			cout << "������� ����" << endl;
			cin >> k;
			b->key = k;
			H.deleteByData(b); //����� Object ��� �������� �������� �� �����
		}
			  break;
		case 4: AAA * c = new AAA;
			cout << "������� ����" << endl;
			cin >> k;
			c->key = k;
			if (H.search(c) == NULL) // ��������� ������ �� ������� ��� �� ������ ����� �� ����� ������������ ������
				cout << "������� �� ������" << endl;
			else
			{
				cout << "������ ������� � ������ ������" << endl;
				AAA_print(H.search(c)); // ���� ������� ���������� ������ ���� ���, �������� � ������ AAA_print 
				cout << endl;
			}
			break;
		}
	}
	return 0;
}
