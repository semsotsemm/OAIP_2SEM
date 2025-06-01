#include <iostream>
#include "function.h"

using namespace std;

FILE* fdata;

void inputToStack(stack*& first)
{
	stack* newel = new stack;
	cout << "������� ����� ��������, ������� ������ �������� � ����: ";
	cin >> newel->value;
	newel->next = first;
	first = newel;
}

void delFromStack(stack*& first)
{
	stack* previous = first, * following = first, * temp;
	int value;
	cout << "������� �������� ��������, ������� ������ �������: ";
	cin >> value;
	if (first->value == value)
	{
		temp = first;
		first = first->next;
		delete(temp);
	}
	else
	{
		while (following->value != value && following != nullptr)
		{
			previous = following;
			following = following->next;
		}
		if (following != nullptr)
		{
			temp = following;
			previous->next = following->next;
			delete(temp);
			cout << "����� " << value << " ������� ������� �� �����:\n";
			showList(first);
		}
		else
		{
			cout << "��������� ����� ��� � ������\n";
		}
	}

}

void showList(stack* first)
{
	stack* continious = first;
	if (first != nullptr)
	{
		while (continious != nullptr)
		{
			cout << continious->value << "-->";
			continious = continious->next;
		}
		cout << "NULL\n";
	}
	else
	{
		cout << "���� ����\n";
	}
}

bool isStackEmpty(stack* first)
{
	return first == nullptr;
}

void inputStackToFile(stack* first)
{
	stack* buf = first;
	if (!fopen_s(&fdata, "data.bin", "ab"))
	{
		while (buf != nullptr)
		{
			fwrite(buf, sizeof(buf), 1, fdata);
			buf = buf->next;
		}
		fclose(fdata);
	}
	else
	{
		cout << "������ �������� �����\n";
	}
}

void readFromFile(stack*& first)
{
	stack* buf = new stack;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(buf, sizeof(buf), 1, fdata))
		{
			buf->next = first;
			first = buf;
			buf = new stack;
		}
		fclose(fdata);
	}
	else
	{
		cout << "������ �������� ����� ��� ������\n";
	}
}

void clear(stack*& first)
{
	while (first != nullptr)
	{
		stack* temp = first;
		first = first->next;
		delete(temp);
	}
}

void buildNewStack(stack* first)
{
	stack* el = new stack, * stack1 = nullptr, * stack2 = nullptr;
	if (first != nullptr)
	{
		while (first != nullptr)
		{
			el->value = first->value;
			if (el->value > 0)
			{
				el->next = stack1;
				stack1 = el;
			}
			else if (el->value < 0)
			{
				el->next = stack2;
				stack2 = el;
			}
			first = first->next;
			el = new stack;
		}
		cout << "stack1 � stack2 ������� ���������:\n\n stack1: ";
		showList(stack1);
		cout << "stack2: ";
		showList(stack2);
	}
	else
	{
		cout << "���� ����\n";
	}
}