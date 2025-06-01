#include <iostream>
#include "function.h"

using namespace std;

void printLine()
{
	cout << "__________________________________________________\n";
}

void printMenu()
{
	cout << "����\n";
	cout << "1 - �������� ����� �������\n";
	cout << "2 - ������� �������\n";
	cout << "3 - ������� ���� � �������\n";
	cout << "4 - �������� ����\n";
	cout << "5 - ������� ������ ������������� �������\n";
	cout << "6 - ��������� � ����\n";
	cout << "7 - �������� ���� �� �����\n";
	cout << "0 - ����� �� ���������\n";
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	stack* head = nullptr;
	int userInput;
	while (true)
	{
		printLine();
		printMenu();
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			pushNewElement(head);
			cout << "��� ����: ";
			printStack(head);
			break;
		case 2:
			popElement(head);
			cout << "������� ������� ������\n";
			cout << "��� ����: ";
			printStack(head);
			break;
		case 3:
			printStack(head);
			break;
		case 4:
			clear(head);
			cout << "���� ������� ������\n";
			break;
		case 5:
			popPositiveElement(head);
			cout << "������ ������������� ������� ������� ������\n";
			cout << "��� ����: ";
			printStack(head);
			break;
		case 6:
			pushStackToFile(head);
			cout << "���� ������� ������� � ����\n";
			break;
		case 7:
			getStackFromFile(head);
			cout << "��� ����: ";
			printStack(head);
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "������ �����\n";
			break;
		}
	}
}