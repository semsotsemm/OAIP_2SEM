#include <iostream>

using namespace std;

void printArr(int* arr, int size) 
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

void countingSort(int* arr, int size)
{
    int* S = new int[size];
    int* arr1 = new int[size];

    for (int i = 0; i < size; i++)
    {
        arr1[i] = arr[i];
        S[i] = 0;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr1[i] > arr1[j] || (arr1[i] == arr1[j] && i > j))
            {
                S[i]++;
            }
        }
    }

    cout << "S: <";
    printArr(S, size);
    cout << ">\n";

    for (int i = 0; i < size; i++)
    {
        arr[S[i]] = arr1[i];
    }

    cout << "Отсортированный массив B: <";
    printArr(arr, size);
    cout << ">\n";

    delete[] S;
    delete[] arr1;
}


int main()
{
	setlocale(2, "Russian");
	srand(time(NULL));
	int size;
	cout << "Введите размер массива B: ";
	cin >> size;
	int* B = new int[size];
	for (int i = 0; i < size; i++)
	{
		B[i] = rand() % 100 + 1;
	}
	cout << "Массив B: < ";
	printArr(B, size);
	cout << ">\n";
	countingSort(B, size);
}