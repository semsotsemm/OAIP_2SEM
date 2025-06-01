#include <iostream>
#include <string>

using namespace std;

struct Queue
{
	int value;
	Queue* next;

	void addNewElement(Queue* newElement);
	void printQueue();
	void deleteElement();
	void clearQueue(Queue* ptr);

	Queue()
	{
		value = 0;
		next = nullptr;
	}
};

Queue* head = nullptr;

void Queue::addNewElement(Queue* newElement)
{
	if (head == nullptr) // Если очередь пуста
	{
		head = newElement;
		return;
	}
	Queue* ptr = head;
	while (ptr->next != nullptr && ptr->next->value < newElement->value)
	{
		ptr = ptr->next;
	}
	if (ptr->next == nullptr)
	{
		if (ptr->value < newElement->value)
		{
			ptr->next = newElement;
		}
		else
		{
			newElement->next = ptr;
			if (ptr == head)
			{
				head = newElement;
			}
		}
	}
	else
	{
		if (ptr == head && newElement->value < head->value)
		{
			head = newElement;
			newElement->next = ptr;
		}
		else
		{
			newElement->next = ptr->next;
			ptr->next = newElement;
		}
	}
	cout << "Элемент успешно добавлен в очередь\n";
}

void Queue::printQueue()
{
	Queue* ptr = head;
	while (ptr != nullptr)
	{
		cout << ptr->value << "-->";
		ptr = ptr->next;
	}
	cout << "NULL\n";
}

void Queue::deleteElement()
{
	Queue* temp = head;
	if (head != nullptr)
	{
		temp = head;
		head = head->next;
		delete[] temp;
	}
	cout << "Элемент успешно удален\n";
}

void Queue::clearQueue(Queue* ptr)
{
	if (ptr->next != nullptr)
	{
		clearQueue(ptr->next);
	}
	delete[] ptr;
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
	for (int i = 0; i < line.length(); i++)
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
		{
			return -1;
		}
	}
	return stoi(line);
}

int main()
{
	string line;
	int userInput;
	setlocale(LC_CTYPE, "Russian");
	printMenu();
	while (true)
	{
		cin >> line;
		userInput = checkInt(line);
		switch (userInput)
		{
		case 1:
		{
			cout << "Введите значение элемента, который хотите добавить: ";
			Queue* newElement = new Queue;
			cin >> newElement->value;
			head->addNewElement(newElement);
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
			head->printQueue();
			break;
		case 5:
			head->clearQueue(head);
			cout << "Очередь очищен\n";
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка ввода, попробуйте еще раз\n";
			break;
		}
	}
}