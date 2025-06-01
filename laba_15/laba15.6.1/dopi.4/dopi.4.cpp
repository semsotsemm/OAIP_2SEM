#include <iostream>

using namespace std;

void printArr(int* arr, int size) 
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}

void shellSorting(int* arr, int size)
{
	for (int step = size / 2; 0 < step; step--)
	{
		for (int i = 0; i < size - step; i ++)
		{
			if (arr[i] < arr[i + step])
			{
				swap(arr[i], arr[i + step]);
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(2, "Russian");
	int size;
	cout << "Введите размер массива: ";
	cin >> size;
	int* A = new int[size];
	for (int i = 0; i < size; i++)
	{
		A[i] = rand() % 100 + 1;
	}
	cout << "Массив А: ";
	printArr(A, size);
	shellSorting(A, size);
	cout << "Массив А, отсортированный методом Шелла: ";
	printArr(A, size);
}