#include <iostream>

using namespace std;

struct numbers
{
	int parm;
	numbers* next;
};

void printLine()
{
	cout << "_______________________________________________\n";
}

void setNewElement(numbers*& head)
{
	numbers* newel = new numbers;
	cout << "Введите элемент который хотите добавить: ";
	cin >> newel->parm;
	newel->next = head;
	head = newel;
	cout << "Элемент успешно добавлен в список\n";
}

void searchElement(numbers* head)
{
	numbers* ptr = head;
	int number, i = 0;
	cout << "Введите какой элемент хотите найти: ";
	cin >> number;
	while (ptr->next != nullptr && ptr->parm != number)
	{
		ptr = ptr->next;
		i++;
	}
	if (ptr->parm == number)
	{
		printLine();
		cout << "Информация ои элементе:\n";
		cout << "Значение: " << ptr->parm << "\n";
		cout << "Следующий элемент: ";
		if (ptr->next == nullptr)
		{
			cout << "-->NULL";
		}
		else
		{
			cout << "-->" << ptr->next->parm;
		}
		cout << "\nНомер в списке: " << i << "\n";
		printLine();
	}
	else
	{
		cout << "Элемента с заданным значением нет в списке\n";
	}
}

void deleteElementFromList(numbers* head)
{
	numbers* ptr = head, * prev = ptr;
	int number;
	cout << "Введите какой элемент хотите удалить: ";
	cin >> number;
	while (ptr->next != nullptr && ptr->parm != number)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr->parm == number)
	{
		prev->next = ptr->next;
		delete(ptr);
		cout << "Элемент успешно удален\n";
	}
	else
	{
		cout << "Элемента с заданным значением нет в списке\n";
	}
}

void printList(numbers* head)
{
	numbers* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->parm << "-->";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

void printListToFile(numbers* head)
{
	FILE* fdata;
	numbers* ptr = head;
	int value;
	if (!fopen_s(&fdata, "data.bin", "ab"))
	{
		while (ptr != nullptr)
		{
			value = ptr->parm;
			fwrite(&value, sizeof(int), 1, fdata);
			ptr = ptr->next;
		}
		fclose(fdata);
		cout << "Список успешно записан в файл data.bin\n";
	}
	else
	{
		cout << "Не удалось открыть файл для записи\n";
	}
}

void outputFromFile(numbers*& head, int el)
{
	numbers* newel = new numbers;
	newel->parm = el;
	newel->next = head;
	head = newel;
}

void getListFromFile(numbers*& head)
{
	FILE* fdata;
	int num;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&num, sizeof(int), 1, fdata))
		{
			outputFromFile(head, num);
		}
		fclose(fdata);
		cout << "Список успешно получен\n";
	}
	else
	{
		cout << "Файл не создан\n";
	}

}

void getSumOfNumbersEndsInThree(numbers* head)
{
	numbers* ptr = head;
	int sum = 0;
	while (ptr != nullptr)
	{
		if (ptr->parm % 10 == 3 && ptr->parm < 0)
		{
			sum += ptr->parm;
		}
		ptr = ptr->next;
	}
	if (sum != 0)
	{
		cout << "Сумма = " << sum << endl;
	}
	else
	{
		cout << "Отрицательных элементов, который оканчиваются на 3 нет в списке\n";
	}
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	numbers* head = nullptr;
	int userInput;
	while (true)
	{
		printLine();
		cout << "Меню:\n";
		cout << "1 - Ввести новый элемент списка\n";
		cout << "2 - Удалить элемент из списка\n";
		cout << "3 - Поиск элемента\n";
		cout << "4 - Вывод списка в консоль\n";
		cout << "5 - Запись списка в файл\n";
		cout << "6 - Получить список из файла\n";
		cout << "7 - Найти сумму положительных двухзначных элементов\n";
		cout << "0 - Выход из программы\n";
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			setNewElement(head);
			cout << "Список: ";
			printList(head);
			break;
		case 2:
			deleteElementFromList(head);
			cout << "Список: ";
			printList(head);
			break;
		case 3:
			searchElement(head);
			break;
		case 4:
			printList(head);
			break;
		case 5:
			printListToFile(head);
			break;
		case 6:
			getListFromFile(head);
			cout << "Список: ";
			printList(head);
			break;
		case 7:
			getSumOfNumbersEndsInThree(head);
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
	}
}