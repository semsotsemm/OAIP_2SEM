#include <iostream>

using namespace std;

struct Tree
{
	int key;
	int parm[3];
	Tree* left, * right;
};

Tree* root = new Tree;

void printLine()
{
	cout << "___________________________________________\n";
}

void printMenu()
{
	printLine();
	cout << "Меню:\n";
	cout << "1 - добавить элемент\n";
	cout << "2 - поиск по ключу\n";
	cout << "3 - удаление элемента по ключу\n";
	cout << "4 - вывод дерева\n";
	cout << "5 - очистка дерева\n";
	cout << "6 - удаление вершины с минимальной суммой 3 значений узла\n";
	cout << "7 - вывод меню\n";
	cout << "8 - выход\n";
	printLine();
}

Tree* insertElement(Tree* ptr, int key)
{
	if (ptr->key < key && ptr->right != nullptr)
	{
		ptr = insertElement(ptr->right, key);
	}
	else if (ptr->key > key && ptr->left != nullptr)
	{
		ptr = insertElement(ptr->left, key);
	}
	return ptr;
}

void addElement()
{
	Tree* branch = new Tree;
	Tree* ptr = root;
	branch->left = nullptr;
	branch->right = nullptr;
	cout << "Введите ключ: ";
	cin >> branch->key;
	cout << "Введите 3 целых числа:\n";
	for (int i = 0; i < 3; i++)
	{
		cout << "Введите " << i + 1 << " целое число: ";
		cin >> branch->parm[i];
	}
	if (ptr->key == NULL)
	{
		root = branch;
	}
	else
	{
		ptr = insertElement(ptr, branch->key);
		if (ptr->key < branch->key)
		{
			ptr->right = branch;
		}
		else
		{
			ptr->left = branch;
		}
	}
}

void outputTree(int level, Tree* ptr)
{
	if (ptr->key != NULL)
	{
		if (ptr->right != nullptr)
		{
			outputTree(level + 1, ptr->right);
		}
		for (int i = 0; i < level; i++)
		{
			cout << "    ";
		}
		cout << ptr->key << ": ";
		for (int i = 0; i < 3; i++)
		{
			cout << ptr->parm[i] << ", ";
		}
		cout << "\n";
		if (ptr->left != nullptr)
		{
			outputTree(level + 1, ptr->left);
		}
	}
	else
	{
		cout << "Дерево не создано (для создания нажмите 1)\n";
	}
}

Tree* searchByKey(Tree* ptr, int key)
{
	if (ptr->key == key)
	{
		return ptr;
	}
	else if (ptr->key < key && ptr->right != nullptr)
	{
		searchByKey(ptr->right, key);
	}
	else if (ptr->key > key && ptr->left != nullptr)
	{
		searchByKey(ptr->left, key);
	}
	else
	{
		printLine();
		cout << "Данного ключа нет в бинарном деревe\n";
		printLine();
		return nullptr;
	}
}

void delByKey(Tree* ptr, int key)
{
	Tree* temp, * prevBranch = nullptr;
	if (ptr->left == nullptr && ptr->right == nullptr)
	{
		printLine();
		cout << "Данного ключа нет в бинарном дереве или значение является корнем\n";
		printLine();
	}
	else if (ptr->right != nullptr && ptr->right->key == key)
	{
		prevBranch = ptr;
	}
	else if (ptr->left != nullptr && ptr->left->key == key)
	{
		prevBranch = ptr;
	}
	else
	{
		if (ptr->key < key && ptr->right != nullptr)
		{
			delByKey(ptr->right, key);
		}
		else if (ptr->key > key && ptr->left != nullptr)
		{
			delByKey(ptr->left, key);
		}
	}
	if (prevBranch != nullptr)
	{
		temp = searchByKey(root, key);
		if (prevBranch->right != nullptr && prevBranch->right->key == key)
		{
			prevBranch->right = temp->right;
			Tree* ptr1 = temp->right;
			if (ptr1 != nullptr)
			{
				while (ptr1->left != nullptr)
				{
					ptr1 = ptr1->left;
				}
				ptr1->left = temp->left;
			}
			delete(temp);
		}
		else
		{
			if (temp->right != nullptr)
			{
				prevBranch->left = temp->right;
				Tree* ptr1 = temp->right;
				while (ptr1->left != nullptr)
				{
					ptr1 = ptr1->left;
				}
				ptr1->left = temp->left;
			}
			else
			{
				prevBranch->left = temp->left;
			}
			delete(temp);
		}
	}
}

Tree* freeCleaning(Tree* ptr)
{
	if (ptr->right != nullptr)
	{
		freeCleaning(ptr->right);
	}
	if (ptr->left != nullptr)
	{
		freeCleaning(ptr->left);
	}
	ptr->left = nullptr;
	ptr->right = nullptr;
	delete(ptr);
	return ptr;
}

int removalMinSum(Tree* ptr, int minSum, int key)
{
	int sum=0;
	if (ptr->right != nullptr)
	{
		key = removalMinSum(ptr->right, minSum, key);
	}
	if (ptr->left != nullptr)
	{
		key = removalMinSum(ptr->left, minSum, key);
	}
	for (int i = 0; i < 3; i++)
	{
		sum += ptr->parm[i];
	}
	if (sum < minSum)
	{
		key = ptr->key;
		minSum = sum;
	}
	return key;
}
int main()
{
	Tree* ptr;
	root->left = nullptr;
	root->right = nullptr;
	root->key = NULL;
	int userInput = 0;
	setlocale(LC_CTYPE, "Russian");
	printMenu();
	while (userInput != 8)
	{
		cin >> userInput;
		switch (userInput)
		{
		case 1:
			addElement();
			break;
		case 2:
		{
			int key;
			cout << "Введите ключ ";
			cin >> key;
			ptr = searchByKey(root, key);
			if (ptr != nullptr)
			{
				printLine();
				cout << "Ключ: " << ptr->key << ", значения: " << ptr->parm[0] << ", " << ptr->parm[1] << ", " << ptr->parm[2] << "\n";
				printLine();
			}
			break;
		}
		case 3:
		{
			int key;
			cout << "Введите ключ ";
			cin >> key;
			delByKey(root, key);
		}
		break;
		case 4:
			outputTree(0, root);
			break;
		case 5:
			root = freeCleaning(root);
			root = new Tree;
			root->left = nullptr;
			root->right = nullptr;
			root->key = NULL;
			break;
		case 6:
		{
			int minSum = 0, key = root->key;
			for (int i = 0; i < 3; i++)
			{
				minSum += root->parm[i];
			}
			key = removalMinSum(root, minSum, key);
			delByKey(root, key);
		}
		break;
		case 7:
			printMenu();
			break;
		case 8:
			break;
		default:
			cout << "Ошибка выбора\n";
			break;
		}
	}
	return 0;
}