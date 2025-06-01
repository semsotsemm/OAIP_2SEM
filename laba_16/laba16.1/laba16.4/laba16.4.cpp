#include <iostream>
#include <string>

using namespace std;

struct Queue {
	int value;
	int id;
	Queue* next;

	Queue() {
		value = 0;
		id = 0;
		next = nullptr;
	}

	void addNewElement(Queue* newElement);
	void printQueue();
	void deleteElement();
	void clearQueue(Queue* ptr);
};

Queue* head = nullptr;
int globalId = 0;

void Queue::addNewElement(Queue* newElement)
{
	newElement->id = globalId++;

	if (head == nullptr || newElement->value < head->value)
	{
		newElement->next = head;
		head = newElement;
	}
	else
	{
		Queue* current = head;
		Queue* previous = nullptr;

		while (current != nullptr && current->value < newElement->value)
		{
			previous = current;
			current = current->next;
		}

		// Вставка в начало блока равных значений (LIFO)
		while (current != nullptr && current->value == newElement->value)
		{
			previous = current;
			current = current->next;
		}

		newElement->next = previous->next;
		previous->next = newElement;
	}

	cout << "Элемент успешно добавлен в очередь\n";
}

void Queue::printQueue()
{
	Queue* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value << "(" << ptr->id << ") --> ";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

void Queue::deleteElement()
{
	if (head == nullptr)
	{
		cout << "Очередь пуста\n";
		return;
	}

	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Queue* prev = nullptr;
		Queue* curr = head;

		while (curr->next != nullptr)
		{
			prev = curr;
			curr = curr->next;
		}
		delete curr;
		prev->next = nullptr;
	}

	cout << "Элемент успешно удален\n";
}

void Queue::clearQueue(Queue* ptr)
{
	if (ptr == nullptr)
		return;

	if (ptr->next != nullptr)
		clearQueue(ptr->next);

	delete ptr;
	head = nullptr;
}

void printLine()
{
	cout << "________________________________\n";
}

void printMenu()
{
	printLine();
	cout << "Меню:\n";
	cout << "1 - Добавить новый элемент в очередь\n";
	cout << "2 - Удалить элемент из очереди\n";
	cout << "3 - Вывод меню в консоль\n";
	cout << "4 - Вывод всей очереди в консоль\n";
	cout << "5 - Очистка очереди\n";
	cout << "0 - Выход\n";
	printLine();
}

int checkInt(string line)
{
	for (char c : line)
		if (!(c >= '0' && c <= '9'))
			return -1;
	return stoi(line);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string line;
	int userInput;
	printMenu();

	while (true)
	{
		cout << "\nВведите команду: ";
		cin >> line;
		userInput = checkInt(line);

		switch (userInput)
		{
		case 1:
		{
			cout << "Введите значение элемента: ";
			Queue* newElement = new Queue;
			cin >> newElement->value;
			newElement->addNewElement(newElement);
			cout << "Текущая очередь: ";
			head->printQueue();
			break;
		}
		case 2:
			head->deleteElement();
			cout << "Текущая очередь: ";
			head->printQueue();
			break;
		case 3:
			printMenu();
			break;
		case 4:
			cout << "Текущая очередь: ";
			head->printQueue();
			break;
		case 5:
			head->clearQueue(head);
			cout << "Очередь очищена\n";
			break;
		case 0:
			return 0;
		default:
			cout << "Ошибка ввода, попробуйте ещё раз\n";
			break;
		}
	}
}
