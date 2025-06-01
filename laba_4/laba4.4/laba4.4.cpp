#include <iostream>
#include <windows.h>

using namespace std;

void input(int size);

void output();

void find(char lastName[]);

typedef struct Students
{
	char fio[16];
	char group[3];
} STUD;

int number; FILE* f; errno_t err;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	int choice; char fio[16];
	do
	{
		cout << "\n1.Ввод данных с клавиатуры и запись в файл\n";
		cout << "2.Вывод данных из файла\n";
		cout << "3.Поиск по фамилии\n";
		cout << "0.Выход из программы\n\n";
		cout << "Введите номер операции: ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "Введите количество студентов: ";
			cin >> number;
			input(number);  break;
		case 2: output(); break;
		case 3: {
			cout << "Введите фамилию: ";
			cin >> fio;
			find(fio); break;
		}
		case 0: exit(0);  break;
		}
	} while (choice != 0);
}

void input(int size)
{
	STUD buf = { ' ', ' ' };
	if (!fopen_s(&f, "base.bin", "ab"))
	{
		for (int p = 0; p < size; p++)
		{
			cout << "Фамилия: "; 	cin >> buf.fio;
			cout << "Группа: "; 	cin >> buf.group;
			fwrite(&buf, sizeof(buf), 1, f);
		}
		fclose(f);
	}
	else {
		cout << "Ошибка открытия файла";
		return;
	}
}

void output()
{
	STUD buf;
	if (!fopen_s(&f, "base.bin", "rb"))
	{
		cout << "\nФамилия    Группа\n";
		fread(&buf, sizeof(buf), 1, f);
		while (!feof(f))
		{
			cout << buf.fio << "\t    " << buf.group << endl;
			fread(&buf, sizeof(buf), 1, f);
		}
		cout << endl;
		fclose(f);
	}
	else
	{
		cout << "Ошибка открытия файла";
		return;
	}
}

void find(char lastName[16])
{
	bool flag = false;  STUD buf;
	if (!fopen_s(&f, "base.bin", "rb"))
	{
		while (!feof(f))
		{
			fread(&buf, sizeof(buf), 1, f);
			if (strcmp(lastName, buf.fio) == 0)   //сравнение строк
			{
				cout << "\nФамилия    Группа\n";
				cout << buf.fio << "\t    " << buf.group << endl;
				flag = true; break;
			}
		}
		fclose(f);
		if (!flag) cout << "Ничего не найдено\n";
	}
	else
	{
		cout << "Ошибка открытия файла";
		return;
	}
}
