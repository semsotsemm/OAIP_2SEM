#include <iostream>

using namespace std;

struct Item
{
	int value;
	Item* next;
};

Item* head, * tail;

void addNewEl()
{
	Item* newValue = new Item;
	Item* before, * after;
	cout << "������� ����� ��������: ";
	cin >> newValue->value;
	if (head == nullptr)
	{
		head = tail = newValue;
		head->next = nullptr;
	}
	else if (newValue->value < head->value)
	{
		newValue->next = head;
		head = newValue;
	}
	else
	{
		before = head;
		after = before->next;
		while (after != nullptr)
		{
			if (newValue->value > after->value)
			{
				before = after;
			}
			after = after->next;
		}
		if (before->next == nullptr)
		{
			newValue->next = nullptr;
			tail->next = newValue;
			tail = tail->next;
		}
		else
		{
			after = before->next;
			newValue->next = after;
			before->next = newValue;
		}
	}
}

void showQueue()
{
	Item* ptr = head;
	if (ptr != nullptr)
	{
		while (ptr != nullptr)
		{
			cout << ptr->value << "-->";
			ptr = ptr->next;
		}
	}
	else 
	{
		cout << "������� �����\n";
	}
	cout << "NULL\n";
}

void getEl() 
{
	cout << "1-�� ������� � �������: " << head->value << endl;
}

void cutEl() 
{
	if (head != nullptr)
	{
		Item* temp = head;
		cout << "�� ������� ��� �������� ������� " << temp->value;
		head = head->next;
		delete(temp);
	}
	else 
	{
		cout << "������: ������� �����\n";
	}
}

void clearQueue() 
{
	while (head != nullptr)
	{
		Item* temp = head;
		head = head->next;
		delete (temp);
	}
	delete(head);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int choice = 1;
	head = nullptr;
	tail = nullptr;
	while (choice != 0)
	{
		cout << "1 - �������� ������� �� ����������" << endl;
		cout << "2 - �������� ������� � ������" << endl;
		cout << "3 - ������� ������� � ������" << endl;
		cout << "4 - ������� ��������" << endl;
		cout << "5 - �������� �������" << endl;
		cout << "0 - �����" << endl;
		cout << "�������� ��������  ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addNewEl();
			cout << "�������:\n";
			showQueue();
			break;
		case 2:
			getEl();
			break;
		case 3:
			cutEl();
			cout << "����� �������:\n";
			showQueue();
			break;
		case 4:
			showQueue();
			break;
		case 5:
			clearQueue();
			cout << "������� ������� �������\n";
			break;
		}
	}
	return 0;
}