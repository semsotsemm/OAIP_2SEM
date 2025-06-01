#include <iostream>  
#include <windows.h> 
#include <string>

#define str_len 30                               

#define size 30  

using namespace std;

void enter_new();

void del();

void change();

void out();

struct Student
{
	char name[str_len];
	int year_of_birth;
	char department[5];
};

struct Student list_of_student[size];

struct Student bad;

int current_size = 0;
int choice;

int main()
{
	string choicecheck;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите:" << endl;
	cout << "1-для удаления записи" << endl;
	cout << "2-для ввода новой записи" << endl;
	cout << "3-для изменения записи" << endl;
	cout << "4-для вывода записи(ей)" << endl;
	cout << "5-для выхода" << endl;
	cin >> choicecheck;
	while (choicecheck != "1" && choicecheck != "2" && choicecheck != "3" && choicecheck != "4" && choicecheck != "5")
	{
		cout << "Ошибка ввода, попробуйте повторить ввод или нажмите 0 для выхода из программы"<<endl;
		cin >> choicecheck;
		if (choicecheck == "0")
		{
			return 0;
		}
	}
	choice = stoi(choicecheck);
	do
	{
		switch (choice)
		{
		case 1:  del();	break;
		case 2:  enter_new();  break;
		case 3:  change();  break;
		case 4:  out();	break;
		}
	} while (choice != 5);
	return 0;
}

void enter_new()
{
	string checkyear;
	int count = 0;
	cout << "Ввод информации" << endl;
	if (current_size < size)
	{
		cout << "Строка номер ";
		cout << current_size + 1;
		cout << endl << "Фамилия: ";
		cin >> list_of_student[current_size].name;
		cout << "Год рождения: ";
		while (true)
		{
			cin >> checkyear;
			for (int i = 0; i < checkyear.length(); i++)
			{
				if (checkyear[i] >= '0' && checkyear[i] <= '9')
				{
					count++;
				}
			}
			if (count == checkyear.length())
			{
				list_of_student[current_size].year_of_birth = stoi(checkyear);
				break;
			}
			else
			{
				cout << "Ошибка ввода, попробуйте повторить ввод, или нажмите 0 для выхода их программы ";
			}
		}
		cout << "Факультет: ";
		cin >> list_of_student[current_size].department;
		current_size++;
	}
	else
		cout << "Введено максимальное кол-во строк";
	cout << "Что дальше?" << endl;
	cin >> choice;
}

void del()
{
	int d;
	cout << "\nНомер строки, которую надо удалить (для удаления всех строк нажать 99)" << endl;  cin >> d;
	if (d != 99)
	{
		for (int de1 = (d - 1); de1 < current_size; de1++) 
		{
			list_of_student[de1] = list_of_student[de1 + 1];
		}
		current_size = current_size - 1;
	}
	if (d == 99)
		for (int i = 0; i < size; i++) 
		{
			list_of_student[i] = bad;
		}
	cout << "Что дальше?" << endl;
	cin >> choice;
}

void change()
{
	int n, per;
	cout << "\nВведите номер строки" << endl; 	cin >> n;
	do
	{
		cout << "Введите: " << endl;
		cout << "1-для изменения фамилии" << endl;
		cout << "2-для изменения года рождения" << endl;
		cout << "3-для изменения факультета" << endl;
		cout << "4-конец\n";
		cin >> per;
		switch (per)
		{
		case 1: cout << "Новая фамилия";
			cin >> list_of_student[n - 1].name;   break;
		case 2: cout << "Новый год рождения";
			cin >> list_of_student[n - 1].year_of_birth; break;
		case 3: cout << "Новый факультет ";
			cin >> list_of_student[n - 1].department; break;
		}
	} while (per != 4);
	cout << "Что дальше?" << endl;
	cin >> choice;
}

void out()
{
	int sw, n;
	cout << "1-вывод 1 строки" << endl;
	cout << "2-вывод всех строк" << endl;
	cin >> sw;
	if (sw == 1)
	{
		cout << "Номер выводимой строки " << endl;   cin >> n;  cout << endl;
		cout << "Фамилия ";
		cout << list_of_student[n - 1].name << endl;
		cout << "Год рождения ";
		cout << list_of_student[n - 1].year_of_birth << endl;
		cout << "Факультет ";
		cout << list_of_student[n - 1].department << endl;
	}
	if (sw == 2)
	{
		for (int i = 0; i < current_size; i++)
		{
			cout << "Фамилия ";
			cout << list_of_student[i].name << endl;
			cout << "Год рождения ";
			cout << list_of_student[i].year_of_birth << endl;
			cout << "Факультет ";
			cout << list_of_student[i].department << endl;
		}
	}
	cout << "Что дальше?" << endl;
	cin >> choice;
}