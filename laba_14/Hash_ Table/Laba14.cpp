#include "Hash_Chain.h"
#include <iostream>
using namespace std;
struct AAA
{
	int key;
	char* mas;
	AAA(int k, char* z) // конструктор для AAA для прямого ввода элемента хеш-таблицы, без участия пользователя (напрямую в коде)
	{
		key = k;
		mas = z;
	}
	AAA() // конструктора для AAA в случае если ничего не передаем при инициализации 
	{
		key = 0; // ключ = 0
		mas = nullptr; //указатель на данные никуда не указывает
	}
};
int hf(void* d)
{
	AAA* f = (AAA*)d; //Преобразуем void* в структуру ААА для возможности образаться к ключу и данным
	return f->key;
}
//-------------------------------
void AAA_print(listx::Element* e)
{
	std::cout << ((AAA*)e->data)->key << '-' << ((AAA*)e->data)->mas << " / "; // выводит определенный элемент в консоль 
}
//-------------------------------
int main()
{
	setlocale(LC_ALL, "rus");
	int current_size = 7;
	cout << "Введите размер хеш-таблицы" << endl;
	cin >> current_size; //Вводим размер таблицы с клавиатуры 
	hashTC::Object H = hashTC::create(current_size, hf); //при помощи метода create создаем хеш-таблицу
	int choice;
	int k;
	for (;;)
	{
		cout << "1 - вывод хеш-таблицы" << endl;
		cout << "2 - добавление элемента" << endl;
		cout << "3 - удаление элемента" << endl;
		cout << "4 - поиск элемента" << endl;
		cout << "0 - выход" << endl;
		cout << "сделайте выбор" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 2: {
			AAA* a = new AAA;
			char* str = new char[20];
			cout << "введите ключ" << endl;
			cin >> k;
			a->key = k;
			cout << "введите строку" << endl;
			cin >> str;
			a->mas = str;
			H.insert(a); // метод Object для вставки новых элементов 
		}
			  break;
		case 1: 
			H.Scan();// метод Object для вывода хеш-таблицы
			break;
		case 3: {
			AAA* b = new AAA;
			cout << "введите ключ" << endl;
			cin >> k;
			b->key = k;
			H.deleteByData(b); //Метод Object для удаления элемента по ключу
		}
			  break;
		case 4: AAA * c = new AAA;
			cout << "введите ключ" << endl;
			cin >> k;
			c->key = k;
			if (H.search(c) == NULL) // проверяем найден ли элемент или мы просто дошли до конца односвязного списка
				cout << "Элемент не найден" << endl;
			else
			{
				cout << "Первый элемент с данным ключом" << endl;
				AAA_print(H.search(c)); // если элемент существует заново ищем его, передаем в фунцию AAA_print 
				cout << endl;
			}
			break;
		}
	}
	return 0;
}
