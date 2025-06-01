#include <iostream>

using namespace std;

struct queue
{
	char symbol;
	queue* next;
};

void printLine()
{
	cout << "___________________________\n";
}

void showMenu()
{
	printLine();
	cout << "Меню:\n" << "1 - Ввод нового символа в очередь\n" << "2 - Удаление символа из очереди\n";
	cout << "3 - Вывести очередь\n" << "4 - Ввести эталонный символ\n" << "5 - Вывод меню\n" << "0 - Выход из программы\n";
	printLine();
	//после эталонного: вывод, удалить 2 эл, вывод, посчитать оставшиеся элементы
}

void inputNewEl(queue*& end, queue*& begin)
{
	queue* newEl = new queue;
	cout << "Введите новый символ очереди: ";
	cin >> newEl->symbol;
	newEl->next = nullptr;
	if (end == nullptr)
	{
		end = newEl;
		begin = newEl;
	}
	else
	{
		end->next = newEl;
		end = newEl;
	}
}

int countQuantity(queue* begin)
{
	int size = 0;
	if (begin != nullptr)
	{
		while (begin != nullptr)
		{
			size++;
			begin = begin->next;
		}
	}
	else
	{
		cout << "Очередь пустая\n";
	}
	return size;
}

void deleteEl(queue*& begin, int quantityEl)
{
	if (quantityEl <= countQuantity(begin))
	{
		for (int i = 0; i < quantityEl; i++)
		{
			queue* temp = begin;
			begin = begin->next;
			delete temp;
		}
	}
	else
	{
		cout << "Ошибка, очередь короче 2 символов, условие не может быть выполненно\n";
	}
}

void showQueue(queue* begin)
{
	if (countQuantity(begin) != 0)
	{
		while (begin != nullptr)
		{
			cout << begin->symbol << " ";
			begin = begin->next;
		}
		cout << "\n";
	}
}

void inputReferenceSymbol(queue*& begin, queue*& end)
{
	char refSymbol;
	queue* newEl;
	cout << "Введите эталонный символ: ";
	cin >> refSymbol;
	cout << "Эталонный символ успешно записан, для того чтобы окончить ввод введите эталонный символ повторно\n";
	do
	{
		newEl = new queue;
		cout << "Введите новый символ очереди: ";
		cin >> newEl->symbol;
		newEl->next = nullptr;
		if (end == nullptr)
		{
			end = newEl;
			begin = newEl;
		}
		else
		{
			end->next = newEl;
			end = newEl;
		}
	} while (newEl->symbol != refSymbol);
	cout << "Вся очередь:\n";
	showQueue(begin);
	cout << "Очередь после удаления 2 символов:\n";
	deleteEl(begin, 2);
	showQueue(begin);
	cout << "Количество оставшихся элементов после удаления: " << countQuantity(begin) << endl;
}

int main()
{
	queue* begin, * end;
	end = begin = nullptr;
	int userInput, quantityEl;
	setlocale(LC_CTYPE, "Russian");
	showMenu();
	cin >> userInput;
	while (userInput != 0)
	{
		switch (userInput)
		{
		case 1:
			inputNewEl(end, begin);
			break;
		case 2:
			cout << "Введите сколько элементов хотите удалить: ";
			cin >> quantityEl;
			deleteEl(begin, quantityEl);
			break;
		case 3:
			showQueue(begin);
			break;
		case 4:
			inputReferenceSymbol(begin, end);
			break;
		case 5:
			showMenu();
			break;
		case 0:
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
		cout << "Что дальше?\n";
		cin >> userInput;
	}
}