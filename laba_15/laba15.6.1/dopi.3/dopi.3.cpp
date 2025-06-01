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

void insertionSort(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j > 0; j--)
		{
			if (arr[j - 1] < arr[j])
			{
				swap(arr[j - 1], arr[j]);
			}
		}
	}
}

int main()
{
	srand(time(NULL));
	setlocale(2, "Russian");
	int size, *A;
	cout << "Введите размер массива: ";
	cin >> size;
	A = new int[size];
}