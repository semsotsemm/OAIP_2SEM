#include <iostream>
#include <string>

using namespace std;

struct tree
{
	int key;
	tree* left;
	tree* right;
	tree()
	{
		left = nullptr;
		right = nullptr;
	}
};

bool checkInt(int& number, string userInput);

void printMenu();

void printLine();

tree* findPrev(tree* root, tree* element);

int getNumbersOfList(tree* root, int numbersOfList);

void printTree(tree* root, int level);

bool pushNewElement(tree*& root, int key);

tree* searchElement(tree* root, int key);

bool popElement(tree* root, int key);

bool insertElement(tree* root, tree* newElement);

bool clearTree(tree*& root);

void initializeTree(tree*& root);

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int number;
	string userInput;
	tree* root = nullptr;
	initializeTree(root);
	printMenu();
	while (true)
	{
		cin >> userInput;
		if (checkInt(number, userInput))
		{
			switch (number)
			{
			case 1:
				printMenu();
				break;
			case 2:
				printTree(root, 0);
				break;
			case 3:
			{
				int key;
				cout << "Введите ключ нового элемента: ";
				cin >> key;
				if (pushNewElement(root, key))
				{
					cout << "Элемент успешно добавлен в бинарное дерево:\n";
					printTree(root, 0);
				}
				else
				{
					cout << "Элемент уже присутствует в бинарном дереве\n";
				}
				break;
			}
			case 4:
			{
				int key;
				cout << "Введите ключ элемента который хотите найти: ";
				cin >> key;
				tree* ptr = searchElement(root, key);
				if (ptr != nullptr)
				{
					cout << "Элемент успешно найден: " << ptr->key << "\n";
				}
				else
				{
					cout << "Элемента нет в бинарном дереве\n";
				}
				break;
			}
			case 5:
			{
				int key;
				cout << "Введите ключ элемента который хотите удалить: ";
				cin >> key;
				if (popElement(root, key))
				{
					cout << "Элемент успешно удален, бинарное дерево:\n";
					printTree(root, 0);
				}
				else
				{
					cout << "Элемента нет в бинарном дереве\n";
				}
				break;
			}
			case 6:
				if (clearTree(root))
				{
					cout << "Дерево успешно очищенно\n";
					root = nullptr;
				}
				else
				{
					cout << "Дерево уже пусто\n";
				}
				break;
			case 7:
			{
				cout << "Количество листьев дерева: " << getNumbersOfList(root, 0) << endl;
				break;
			}
			case 0:
				exit(0);
				break;
			default:
				cout << "Ошибка ввода\n";
				break;
			}
		}
		else
		{
			cout << "Ошибка ввода\n";
		}
	}
}

void printMenu()
{
	printLine();
	cout << "Меню:\n";
	cout << "1 - Вывод меню в консоль\n";
	cout << "2 - Вывод бинарного дерева в консоль\n";
	cout << "3 - Добавить элемент в бинарное дерево\n";
	cout << "4 - Поиск элемента по ключу\n";
	cout << "5 - Удалить элемент из бинарного дерева\n";
	cout << "6 - Очистить бинарное дерево\n";
	cout << "7 - Посчитать количества листьев дерева\n";
	cout << "0 - Выход из программы\n";
	printLine();
}

bool checkInt(int& number, string userInput)
{
	int repeat = 0;
	for (int i = 0; i < userInput.length(); i++)
	{
		if (userInput[i] >= '0' && userInput[i] <= '9')
		{
			repeat++;
		}
	}
	if (userInput.length() == repeat)
	{
		number = stoi(userInput);
	}
	return userInput.length() == repeat;
}

void initializeTree(tree*& root)
{
	pushNewElement(root, 9);
	pushNewElement(root, 14);
	pushNewElement(root, 18);
	pushNewElement(root, 11);
	pushNewElement(root, 10);
	pushNewElement(root, 4);
	pushNewElement(root, 6);
	pushNewElement(root, 5);
	pushNewElement(root, 2);
}

void printLine()
{
	cout << "________________________________\n";
}

int getNumbersOfList(tree* root, int numbersOfList)
{
	if (root == nullptr)
	{
		cout << "Дерево не созданно\n";
	}
	else
	{
		if (root->right != nullptr)
		{
			numbersOfList = getNumbersOfList(root->right, numbersOfList);
		}
		if (root->left != nullptr)
		{
			numbersOfList = getNumbersOfList(root->left, numbersOfList);
		}
		else
		{
			return numbersOfList + 1;
		}
	}
	return numbersOfList;
}

void printTree(tree* root, int level)
{
	if (root == nullptr)
	{
		cout << "Дерево не созданно\n";
	}
	else
	{
		if (root->right != nullptr)
		{
			printTree(root->right, level + 1);
		}
		for (int i = 0; i < level; i++)
		{
			cout << "         ";
		}
		cout << root->key << "\n";
		if (root->left != nullptr)
		{
			printTree(root->left, level + 1);
		}
	}
}

bool pushNewElement(tree*& root, int key)
{
	tree* newElement = new tree;
	newElement->key = key;
	if (root == nullptr)
	{
		root = newElement;
		return true;
	}
	else
	{
		return insertElement(root, newElement);
	}
}

bool insertElement(tree* root, tree* newElement)
{
	if (root->right != nullptr && root->key < newElement->key)
	{
		return insertElement(root->right, newElement);
	}
	if (root->left != nullptr && root->key > newElement->key)
	{
		return insertElement(root->left, newElement);
	}
	if (root->right == nullptr && root->key <= newElement->key)
	{
		if (root->key == newElement->key)
		{
			delete(newElement);
			return false;
		}
		root->right = newElement;
		return true;
	}
	else if (root->left == nullptr && root->key >= newElement->key)
	{
		if (root->key == newElement->key)
		{
			delete(newElement);
			return false;
		}
		root->left = newElement;
		return true;
	}
}

tree* searchElement(tree* root, int key)
{
	tree* ptr = nullptr;
	if (root->right != nullptr && key > root->key)
	{
		ptr = searchElement(root->right, key);
	}
	if (root->left != nullptr && key < root->key)
	{
		ptr = searchElement(root->left, key);
	}
	if (root->key == key)
	{
		ptr = root;
	}
	return ptr;
}

tree* findPrev(tree* root, tree* element)
{
	tree* ptr = nullptr;
	if (root->right != nullptr && element->key > root->key)
	{
		ptr = findPrev(root->right, element);
	}
	if (root->left != nullptr && element->key < root->key)
	{
		ptr = findPrev(root->left, element);
	}
	if (root->right != nullptr && root->right->key == element->key)
	{
		ptr = root;
	}
	if (root->left != nullptr && root->left->key == element->key)
	{
		ptr = root;
	}
	return ptr;
}

bool popElement(tree* root, int key)
{
	tree* element = searchElement(root, key);
	if (element != nullptr && element != root)
	{
		tree* prev = findPrev(root, element);
		tree* rightBranch = element;
		if (rightBranch->left != nullptr)
		{
			if (rightBranch->right != nullptr)
			{
				rightBranch = rightBranch->right;
				while (rightBranch->left != nullptr)
				{
					rightBranch = rightBranch->left;
				}
				rightBranch->left = element->left;
				element->left = nullptr;
			}
			else
			{
				rightBranch->right = rightBranch->left;
			}
		}
		if (prev->right != nullptr && prev->right == element)
		{
			prev->right = element->right;
			delete(element);
		}
		else if (prev->left != nullptr && prev->left == element)
		{
			prev->left = element->right;
			delete(element);
		}
		return true;
	}
	else if (element != nullptr && element == root)
	{
		if (root->right != nullptr)
		{
			root = root->right;
		}
		else if (root->left != nullptr)
		{
			root = root->left;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool clearTree(tree*& root)
{
	if (root == nullptr)
	{
		return false;
	}
	else
	{
		if (root->right != nullptr)
		{
			clearTree(root->right);
		}
		if (root->left != nullptr)
		{
			clearTree(root->left);
		}
		delete(root);
		return true;
	}
}