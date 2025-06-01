#include <iostream>
#include <fstream>

using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
	char name[NAME_SIZE];
	char city[CITY_SIZE];
	Address* next;
	Address* prev;
};

void writeToFile(Address** phead)       //Запись в файл
{
	struct Address* t = *phead;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist.txt", "wb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	cout << "Сохранение в файл" << endl;
	while (t)
	{
		fwrite(t, sizeof(struct Address), 1, fp);
		t = t->next;
	}
	fclose(fp);
}

int menu(void)
{
	char s[80];
	int c;
	cout << endl;
	cout << "1. Ввод имени" << endl;
	cout << "2. Удаление имени" << endl;
	cout << "3. Вывод на экран" << endl;
	cout << "4. Поиск" << endl;
	cout << "5. Запись в файл" << endl;
	cout << "6. Чтение из файла" << endl;
	cout << "7. Удаление повторяющихся данных" << endl;
	cout << "8. Выход" << endl;
	cout << endl;
	do
	{
		cout << "Ваш выбор: ";
		cin.sync();
		gets_s(s);
		cout << endl;
		c = atoi(s);
	} while (c < 0 || c > 9);
	return c;
}

void insert(Address* e, Address** phead, Address** plast) //Добавление в конец списка
{
	Address* p = *plast;
	if (*plast == nullptr)
	{
		e->next = nullptr;
		e->prev = nullptr;
		*plast = e;
		*phead = e;
		return;
	}
	else
	{
		p->next = e;
		e->next = nullptr;
		e->prev = p;
		*plast = e;
	}
}

void readFromFile(Address** phead, Address** plast)   //Считывание из файла
{
	Address* t;
	FILE* fp;
	errno_t err = fopen_s(&fp, "mlist.txt", "rb");
	if (err)
	{
		cerr << "Файл не открывается" << endl;
		exit(1);
	}
	while (*phead)
	{
		*plast = (*phead)->next;
		delete* phead;
		*phead = *plast;
	}
	*phead = *plast = nullptr;
	cout << "Загрузка из файла" << endl;
	while (!feof(fp))
	{
		t = new Address();
		if (!t)
		{
			cerr << "Ошибка выделения памяти" << endl;
			return;
		}
		if (1 != fread(t, sizeof(struct Address), 1, fp)) break;
		insert(t, phead, plast);
	}
	fclose(fp);
}

Address* setElement()      // Создание элемента и ввод его значений с клавиатуры 
{
	Address* temp = new Address();
	if (!temp)
	{
		cerr << "Ошибка выделения памяти памяти";
		exit(1);
	}
	cout << "Введите имя: ";
	cin.getline(temp->name, NAME_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	cout << "Введите город: ";
	cin.getline(temp->city, CITY_SIZE - 1, '\n');
	cin.ignore(cin.rdbuf()->in_avail());
	cin.clear();
	temp->next = nullptr;
	temp->prev = nullptr;
	return temp;
}

void outputList(Address** phead, Address** plast)      //Вывод списка на экран
{
	Address* t = *phead;
	while (t)
	{
		cout << t->name << ' ' << t->city << endl;
		t = t->next;
	}
	cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead)    // Поиск имени в списке
{
	Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name)) break;
		t = t->next;
	}
	if (!t)
		cerr << "Имя не найдено" << endl;
	else
		cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast)  // Удаление имени
{
	Address* t = *phead;
	while (t)
	{
		if (!strcmp(name, t->name))
		{
			break;
		}
		t = t->next;
	}
	if (!t)
	{
		cerr << "Имя не найдено" << endl;
	}
	else
	{
		if (*phead == t)
		{
			*phead = t->next;
			if (*phead)
			{
				(*phead)->prev = nullptr;
			}
			else
			{
				*plast = nullptr;
			}
		}
		else
		{
			t->prev->next = t->next;
			if (t != *plast)
			{
				t->next->prev = t->prev;
			}
			else
			{
				*plast = t->prev;
			}
		}
		delete t;
		cout << "Элемент удален" << endl;
	}
}

void deleteDouble(Address** phead, Address** plast)
{
	Address* ptr1 = *phead;
	while (ptr1)
	{
		Address* ptr2 = ptr1->next;
		while (ptr2)
		{
			if (strcmp(ptr1->name, ptr2->name) == 0)
			{
				Address* duplicate = ptr2;
				ptr2 = ptr2->next;

				if (duplicate == *plast)
					*plast = duplicate->prev;
				if (duplicate->prev)
					duplicate->prev->next = duplicate->next;
				if (duplicate->next)
					duplicate->next->prev = duplicate->prev;

				delete duplicate;
			}
			else
			{
				ptr2 = ptr2->next;
			}
		}
		ptr1 = ptr1->next;
	}
	cout << "Дубликаты удалены." << endl;
}

int main()
{
	Address* head = nullptr;
	Address* last = nullptr;
	setlocale(LC_CTYPE, "Russian");
	while (true)
	{
		switch (menu())
		{
		case 1:
			insert(setElement(), &head, &last);
			break;
		case 2: {
			char dname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(dname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			delet(dname, &head, &last);
		}
			  break;
		case 3:
			outputList(&head, &last);
			break;
		case 4:
		{
			char fname[NAME_SIZE];
			cout << "Введите имя: ";
			cin.getline(fname, NAME_SIZE - 1, '\n');
			cin.ignore(cin.rdbuf()->in_avail());
			cin.sync();
			find(fname, &head);
		}
		break;
		case 5:
			writeToFile(&head);
			break;
		case 6:
			readFromFile(&head, &last);
			break;
		case 7:
			deleteDouble(&head, &last);
			break;
		case 8:
			exit(0);
		default:
			exit(1);
		}
	}
	return 0;
}