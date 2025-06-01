#include <iostream>
#include "function.h"
#include <fstream>

using namespace std;

Student* firstStudent = nullptr, * lastStudent = nullptr;

void printLine()
{
	cout << "_________________________\n";
}

void addStudent()
{
	Student* temp = new Student, * ptr = firstStudent;
	printLine();
	cout << "������� ������ ��������:\n";
	cout << "�������: ";
	cin.ignore();
	cin.getline(temp->secondname, 20);
	cout << "���: ";
	cin.getline(temp->name, 20);
	cout << "��������: ";
	cin.getline(temp->surname, 20);
	cout << "��� ��������: ";
	cin >> temp->yearOfBirth;
	cout << "�� ����� ����� ������ �������: ";
	cin >> temp->course;
	cout << "������: ";
	cin >> temp->group;
	cout << "������ �� ������� �� ����: ";
	cin >> temp->oaipGrade;
	cout << "������ �� ������� �� ���: ";
	cin >> temp->opiGrade;
	cout << "������ �� ������� �� �����������: ";
	cin >> temp->englishGrade;
	cout << "������ �� ������� �� �����������: ";
	cin >> temp->mathemathicsGrade;
	cout << "������ �� ������� �� ������: ";
	cin >> temp->physicsGrade;
	printLine();
	temp->next = nullptr;
	temp->previous = nullptr;
	if (firstStudent == nullptr)
	{
		firstStudent = lastStudent = temp;
	}
	else
	{
		while (ptr->next != nullptr && ptr->course < temp->course)
		{
			ptr = ptr->next;
		}
		if (ptr->next == nullptr)
		{
			temp->previous = ptr;
			ptr->next = temp;
			lastStudent = lastStudent->next;
		}
		else
		{
			while (ptr->next != nullptr && ptr->secondname[0] < temp->secondname[0])
			{
				ptr = ptr->next;
			}
			if (ptr->next == nullptr)
			{
				temp->previous = ptr;
				ptr->next = temp;
				lastStudent = lastStudent->next;
			}
			else if (ptr->previous == nullptr)
			{
				temp->next = ptr;
				ptr->previous = temp;
				firstStudent = firstStudent->previous;
			}
			else
			{
				temp->previous = ptr->previous;
				temp->previous->next = temp;
				temp->next = ptr;
				ptr->previous = temp;
			}
		}
	}
	cout << "������� ������� �������";
}

void showList()
{
	Student* ptr = firstStudent;
	for (int i = 1; i <= 4; i++)
	{
		cout << "##################### " << i << " ���� #####################\n";
		while (ptr != nullptr)
		{
			if (ptr->course == i)
			{
				printLine();
				cout << "�������: " << ptr->secondname << endl;
				cout << "���: " << ptr->name << endl;
				cout << "��������: " << ptr->surname << endl;
				cout << "��� ��������: " << ptr->yearOfBirth << endl;
				cout << "����: " << ptr->course << endl;
				cout << "������: " << ptr->group << endl;
				cout << "������ �� ������� �� ����: " << ptr->oaipGrade << endl;
				cout << "������ �� ������� �� ���: " << ptr->opiGrade << endl;
				cout << "������ �� ������� �� �����������: " << ptr->englishGrade << endl;
				cout << "������ �� ������� �� �����������: " << ptr->mathemathicsGrade << endl;
				cout << "������ �� ������� �� ������: " << ptr->physicsGrade << endl;
				printLine();
			}
			ptr = ptr->next;
		}
		ptr = firstStudent;
	}
}

void readList()
{
	ifstream fdata("data.txt");
	Student* temp = new Student, * ptr;
	string buf;
	if (fdata.is_open())
	{
		while (!fdata.eof())
		{
			ptr = firstStudent;
			fdata >> buf;
			strcpy_s(temp->secondname, sizeof(temp->secondname), buf.c_str());
			fdata >> buf;
			strcpy_s(temp->name, sizeof(temp->name), buf.c_str());
			fdata >> buf;
			strcpy_s(temp->surname, sizeof(temp->surname), buf.c_str());
			fdata >> temp->yearOfBirth;
			fdata >> temp->course;
			fdata >> temp->group;
			fdata >> temp->oaipGrade;
			fdata >> temp->opiGrade;
			fdata >> temp->englishGrade;
			fdata >> temp->mathemathicsGrade;
			fdata >> temp->physicsGrade;
			temp->next = nullptr;
			temp->previous = nullptr;
			if (firstStudent == nullptr)
			{
				firstStudent = lastStudent = temp;
			}
			else
			{
				while (ptr->next != nullptr && ptr->course < temp->course)
				{
					ptr = ptr->next;
				}
				if (ptr->next == nullptr)
				{
					temp->previous = ptr;
					ptr->next = temp;
					lastStudent = lastStudent->next;
				}
				else
				{
					while (ptr->next != nullptr && ptr->secondname[0] < temp->secondname[0])
					{
						ptr = ptr->next;
					}
					if (ptr->next == nullptr)
					{
						temp->previous = ptr;
						ptr->next = temp;
						lastStudent = lastStudent->next;
					}
					else if (ptr->previous == nullptr)
					{
						temp->next = ptr;
						ptr->previous = temp;
						firstStudent = firstStudent->previous;
					}
					else
					{
						temp->previous = ptr->previous;
						temp->previous->next = temp;
						temp->next = ptr;
						ptr->previous = temp;
					}
				}
			}
			temp = new Student;
		}
		fdata.close();
	}
	else
	{
		cout << "�� ������� ������� ���� data.txt ��� ������\n";
	}
}

void calculateAverageScore()
{
	Student* ptr = firstStudent;
	double quantity = 0, sum = 0;
	int userInput[3]; //0 - ����, 1 ������, 2 - ��������
	cout << "������� ���� ���������, ��� ������� ���� ������ ���������: ";
	cin >> userInput[0];
	cout << "������� ������ ���������, ��� ������� ���� ������ ���������: ";
	cin >> userInput[1];
	cout << "������� ��������, �� �������� ������ ��������� ������� ���� ";
	cout << "(1 - ����, 2 - ���, 3 - ���������, 4 - ����������, 5 - ������):";
	cin >> userInput[2];
	while (ptr != nullptr)
	{
		if (userInput[0] == ptr->course && userInput[1] == ptr->group)
		{
			switch (userInput[2])
			{
			case 1:
				sum += ptr->oaipGrade;
				break;
			case 2:
				sum += ptr->opiGrade;
				break;
			case 3:
				sum += ptr->englishGrade;
				break;
			case 4:
				sum += ptr->mathemathicsGrade;
				break;
			case 5:
				sum += ptr->physicsGrade;
				break;
			default:
				cout << "������ �����";
				break;
			}
			quantity++;
		}
		ptr = ptr->next;
	}
	cout << "������� ���� ������ �� ��������� ��������: " << sum / quantity << endl;
}

void findYoungest()
{
	Student* ptr = firstStudent, * youngestStudent = firstStudent;
	int age = 0;
	while (ptr != nullptr)
	{
		if (age < ptr->yearOfBirth)
		{
			age = ptr->yearOfBirth;
			youngestStudent = ptr;
		}
		ptr = ptr->next;
	}
	cout << "������� ��������� ��������: " << youngestStudent->secondname << " " << youngestStudent->name << " " << youngestStudent->surname;
	cout << " (" << 2025 - age << " ���)\n";
}

void findOldest()
{
	Student* ptr = firstStudent, * oldestStudent = firstStudent;
	int age = 3000;
	while (ptr != nullptr)
	{
		if (age > ptr->yearOfBirth)
		{
			age = ptr->yearOfBirth;
			oldestStudent = ptr;
		}
		ptr = ptr->next;
	}
	cout << "������� ��������� ��������: " << oldestStudent->secondname << " " << oldestStudent->name << " " << oldestStudent->surname;
	cout << " (" << 2025 - age << " ���)\n";
}

void findTheBestStudent()
{
	Student* ptr = firstStudent, * bestStudent = firstStudent;
	int sum = 0, maxSum = 0;
	int userInput[3]; //0 - ����, 1 ������
	cout << "������� ����, �� ������� ������ ����� ������� � ����� ������ ������������, ��������: ";
	cin >> userInput[0];
	cout << "������� ������, � ������� ������ ����� ������� � ����� ������ ������������, ��������: ";
	cin >> userInput[1];
	while (ptr != nullptr)
	{
		if (userInput[0] == ptr->course && userInput[1] == ptr->group)
		{
			sum = ptr->englishGrade + ptr->mathemathicsGrade + ptr->oaipGrade + ptr->opiGrade + ptr->physicsGrade;
			if (sum > maxSum)
			{
				maxSum = sum;
				bestStudent = ptr;
			}
		}
		ptr = ptr->next;
	}
	printLine();
	cout << "������ ������� � ����� ������ ������������:\n";
	cout << "�������: " << bestStudent->secondname << endl;
	cout << "���: " << bestStudent->name << endl;
	cout << "��������: " << bestStudent->surname << endl;
	cout << "��� ��������: " << bestStudent->yearOfBirth << endl;
	cout << "����: " << bestStudent->course << endl;
	cout << "������: " << bestStudent->group << endl;
	cout << "������ �� ������� �� ����: " << bestStudent->oaipGrade << endl;
	cout << "������ �� ������� �� ���: " << bestStudent->opiGrade << endl;
	cout << "������ �� ������� �� �����������: " << bestStudent->englishGrade << endl;
	cout << "������ �� ������� �� �����������: " << bestStudent->mathemathicsGrade << endl;
	cout << "������ �� ������� �� ������: " << bestStudent->physicsGrade << endl;
	printLine();
}