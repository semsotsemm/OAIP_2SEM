#include <iostream>
#include <fstream>
#include "myStack.h"

using namespace std;

void push(char x, Stack*& myStk)   //���������� �������� � � ����	
{
	Stack* e = new Stack;    //��������� ������ ��� ������ ��������
	e->data = x;             //������ �������� x � ���� data 
	e->next = myStk;         //������� ������� �� ��������� ������� 
	myStk = e;               //����� ������� �� ������� ������
}

char pop(Stack*& myStk)   //���������� (��������) �������� �� �����
{
	if (myStk == nullptr)
	{
		cout << "���� ����!" << endl;
		return -1;               //���� ���� ���� - ������� (-1) 
	}
	else
	{
		Stack* e = myStk;        //�-���������� ��� �������� ������ ��������
		char x = myStk->data;    //������ �������� �� ���� data � �����. x 
		if (myStk != nullptr) 
		{
			myStk = myStk->next;   //������� �������
		}
		delete e;
		return x;
	}
}
void toFile(Stack*& myStk) //������ � ����
{
	Stack* e = myStk;
	Stack buf;
	ofstream frm("mStack.dat");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	while (e != nullptr)
	{
		buf = *e;
		frm.write((char*)&buf, sizeof(Stack));
		e = e->next;
	}
	frm.close();
	cout << "���� ������� � ���� mStack.dat\n";
}

void fromFile(Stack*& myStk)          //���������� �� �����
{
	Stack buf, * p = nullptr, * e = nullptr;
	ifstream frm("mStack.dat");
	if (frm.fail())
	{
		cout << "\n ������ �������� �����";
		exit(1);
	}
	frm.seekg(0);
	frm.read((char*)&buf, sizeof(Stack));
	while (!frm.eof())
	{
		push(buf.data, e);
		frm.read((char*)&buf, sizeof(Stack));
	}
	frm.close();
	while (e != nullptr)
	{
		buf.data = pop(e);
		push(buf.data, p);
		myStk = p;
	}
	cout << "\n���� ������ �� ����� mStack.dat\n\n";
}
void show(Stack*& myStk)  //����� ����� � ��������
{
	Stack* e = myStk;
	if (e == nullptr) 
	{
		cout << "���� ����!" << endl;
	}
	while (e != nullptr)
	{
		cout << pop(e) << " ";
	}	
	cout << endl;
}
