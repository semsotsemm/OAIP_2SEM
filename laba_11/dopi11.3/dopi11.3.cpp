#include <iostream>
#include <string>

using namespace std;

struct tree
{
	int key;
	string line;
	tree* left;
	tree* right;
	tree()
	{
		left = nullptr;
		right = nullptr;
	}
};

void printLine();

void printMenu();

void pushNewElement(tree*& root);

tree* insertElement(int key, tree* ptr);

tree* foundElement(tree* root, int key);

void printTree(tree* root, int level);

void cleanTree(tree*& root);

bool deleteElement(tree*& root, int key);

tree* foundPrev(tree* root, tree* ptr);

void printByLevel(tree* root, int level);

void printBranchKey(tree* ptr);

void printBranchLine(tree* ptr);

int main()
{
	setlocale(2, "Russian");
	int userInput;
	printLine();
	printMenu();
	printLine();
	tree* root = nullptr;
	setlocale(LC_CTYPE, "Russian");
	while (true)
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			pushNewElement(root);
			cout << "Элемент успешно записан в бинарное дерево:\n";
			printTree(root, 0);
			break;
		case 2:
			printTree(root, 0);
			break;
		case 3:
		{
			cout << "Введите ключ искомого элемента: ";
			int key;
			tree* ptr = root;
			cin >> key;
			ptr = foundElement(ptr, key);
			if (ptr != nullptr)
			{
				cout << "Элемент найден, информация о элементе:\n";
				cout << "Ключ: " << ptr->key << endl;
				cout << "Строка: " << ptr->line << endl;
			}
			else
			{
				cout << "Данного элемента нет в бинарном дереве\n";
			}
			break;
		}
		case 4:
		{
			cout << "Введите ключ элемента, который хотите удалить: ";
			int key;
			cin >> key;
			if (deleteElement(root, key))
			{
				cout << "Элемент успешно удален\n";
				cout << "Итоговое бинарное дерево:\n";
				printTree(root, 0);
			}
			else
			{
				cout << "Данного элемента нет в бинарном дереве\n";
			}
			break;
		}
		case 5:
			cleanTree(root);
			root = nullptr;
			cout << "Дерево успешно очищенно\n";
			break;
		case 6:
			printLine();
			printMenu();
			printLine();
			break;
		case 7:
			if (root != nullptr)
			{
				cout << "Ключ корня: " << root->key << "; Строка корня: " << root->line << "\n";
				printByLevel(root, 1);
			}
			else
			{
				cout << "Дерево не созданно\n";
			}
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Ошибка ввода\n";
			break;
		}
	}
	return 0;
}

void printLine()
{
	cout << "______________________________________\n";
}

void printMenu()
{
	cout << "Меню\n";
	cout << "1 - Добавить новый элемент в бинарное дерево\n";
	cout << "2 - Вывести в консоль бинарное дерево\n";
	cout << "3 - Найти элемент по ключу\n";
	cout << "4 - Удалить элемент из бинарного дерева\n";
	cout << "5 - Очистка дерева\n";
	cout << "6 - Вывод меню\n";
	cout << "7 - Вывод всех элементов дерева по уровням\n";
	cout << "0 - Выход из программы\n";
}

void printByLevel(tree* root, int level)
{
	if (root != nullptr)
	{
		if (root->right != nullptr || root->left != nullptr)
		{
			cout << "Ключи " << level << "-ого уровня: ";
			printBranchKey(root);
			cout << "; Строки " << level << "-ого уровня: ";
			printBranchLine(root);
			cout << ";\n";
		}
		if (root->right != nullptr)
		{
			printByLevel(root->right, level + 1);
		}
		if (root->left != nullptr)
		{
			printByLevel(root->left, level + 1);
		}
	}
}

void printBranchKey(tree* ptr)
{
	if (ptr->right != nullptr)
	{
		cout << ptr->right->key << " ";
	}
	if (ptr->left != nullptr)
	{
		cout << ptr->left->key << " ";
	}
}

void printBranchLine(tree* ptr)
{
	if (ptr->right != nullptr)
	{
		cout << ptr->right->line << " ";
	}
	if (ptr->left != nullptr)
	{
		cout << ptr->left->line << " ";
	}
}

void pushNewElement(tree*& root)
{
	tree* newElement = new tree, * ptr;
	cout << "Введите ключ: ";
	cin >> newElement->key;
	cout << "Введите строку для данного ключа: ";
	cin.ignore();
	getline(cin, newElement->line);
	if (root == nullptr)
	{
		root = newElement;
	}
	else
	{
		ptr = insertElement(newElement->key, root);
		if (newElement->key > ptr->key)
		{
			ptr->right = newElement;
		}
		else
		{
			ptr->left = newElement;
		}
	}
}

tree* insertElement(int key, tree* ptr)
{
	if (key >= ptr->key && ptr->right != nullptr)
	{
		ptr = insertElement(key, ptr->right);
	}
	else if (key < ptr->key && ptr->left != nullptr)
	{
		ptr = insertElement(key, ptr->left);
	}
	return ptr;
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
		cout << root->key << ": " << root->line << "\n";
		if (root->left != nullptr)
		{
			printTree(root->left, level + 1);
		}
	}
}

tree* foundElement(tree* root, int key)
{
	tree* ptr = nullptr;
	if (root->key < key && root->right != nullptr)
	{
		ptr = foundElement(root->right, key);
	}
	if (root->key > key && root->left != nullptr)
	{
		ptr = foundElement(root->left, key);
	}
	if (root->key == key)
	{
		return root;
	}
	return ptr;
}

void cleanTree(tree*& root)
{
	if (root->right != nullptr)
	{
		cleanTree(root->right);
	}
	if (root->left != nullptr)
	{
		cleanTree(root->left);
	}
	delete(root);
}

bool deleteElement(tree*& root, int key)
{
	tree* ptr = foundElement(root, key);
	if (ptr == nullptr)
	{
		return false;
	}
	tree* prev = foundPrev(root, ptr), * rightEnd;
	if (prev->right != nullptr && prev->right == ptr)
	{
		if (ptr->right != nullptr)
		{
			if (ptr->left != nullptr)
			{
				rightEnd = ptr->right;
				while (rightEnd->left != nullptr)
				{
					rightEnd = rightEnd->left;
				}
				rightEnd->left = ptr->left;
				ptr->left = nullptr;
			}
		}
		else if (ptr->left != nullptr)
		{
			ptr->right = ptr->left;
			ptr->left = nullptr;
		}
		prev->right = ptr->right;
		delete(ptr);
		return true;
	}
	else if (prev->left != nullptr && prev->left == ptr)
	{
		if (ptr->left != nullptr)
		{
			if (ptr->right != nullptr)
			{
				rightEnd = ptr->left;
				while (rightEnd->right != nullptr)
				{
					rightEnd = rightEnd->right;
				}
				rightEnd->right = ptr->right;
				ptr->right = nullptr;
			}
		}
		else if (ptr->right != nullptr)
		{
			ptr->left = ptr->right;
			ptr->right = nullptr;
		}
		prev->left = ptr->left;
		delete(ptr);
		return true;
	}
	else if (ptr == root)
	{
		if (ptr->right != nullptr)
		{
			if (ptr->left != nullptr)
			{
				rightEnd = ptr->right;
				while (rightEnd->left != nullptr)
				{
					rightEnd = rightEnd->left;
				}
				rightEnd->left = ptr->left;
				ptr->left = nullptr;
			}
		}
		else if (ptr->left != nullptr)
		{
			ptr->right = ptr->left;
			ptr->left = nullptr;
		}
		ptr = ptr->right;
		delete(root);
		root = ptr;
		return true;
	}
}

tree* foundPrev(tree* prev, tree* ptr)
{
	if ((prev->right != nullptr && prev->right == ptr) || (prev->left != nullptr && prev->left == ptr))
	{
		return prev;
	}
	if (prev->right != nullptr && prev->right->key > ptr->key)
	{
		prev = foundPrev(prev->right, ptr);
	}
	else if (prev->left != nullptr && prev->left->key < ptr->key)
	{
		prev = foundPrev(prev->right, ptr);
	}
	return prev;
}