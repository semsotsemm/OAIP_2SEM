#include <iostream>
#include <chrono>

using namespace std;

struct Timer
{
	int milliseconds;
	int seconds;
	int minutes;
	chrono::time_point<chrono::high_resolution_clock> start_time;
	chrono::time_point<chrono::high_resolution_clock> end_time;

	void start()
	{
		start_time = chrono::high_resolution_clock::now();
	}
	void stop()
	{
		end_time = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

		milliseconds = duration.count() % 1000;
		seconds = (duration.count() / 1000) % 60;
		minutes = (duration.count() / 1000 / 60) % 60;
	}
	void getTime()
	{
		cout << minutes << "м. " << seconds << "с. " << milliseconds << "мс.\n";
	}
};

void printArray(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << "\n";
}

void bubbleSort(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void heapify(int* arr, int size, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && arr[left] < arr[largest])
	{
		largest = left;
	}
	if (right < size && arr[right] < arr[largest])
	{
		largest = right;
	}
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, size, largest);
	}
}

void piramidSort(int* arr, int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		heapify(arr, size, i);
	}
	for (int i = size - 1; i > 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}


int main()
{
	setlocale(LC_CTYPE, "Russian");
	srand(time(NULL));
	Timer time;
	int* A, * B, sizeA, sizeB;
	cout << "Введите размер массива А: ";
	cin >> sizeA;
	sizeB = int((sizeA + 1) / 2);
	A = new int[sizeA];
	B = new int[sizeB];
	for (int i = 0, j = 0; i < sizeA; i++)
	{
		A[i] = rand() % 100 + 1;
		if (i % 2 == 0)
		{
			B[j++] = A[i];
		}
	}
	cout << "Массив A:\n";
	printArray(A, sizeA);
	cout << "Неотсортированный массив B:\n";
	printArray(B, sizeB);
	time.start();
	bubbleSort(B, sizeB);
	time.stop();
	cout << "Массив B отсортирован пузырьковой сортировкой:\n";
	printArray(B, sizeB);
	cout << "Сортировка заняла: ";
	time.getTime();
	for (int i = 0, j = 0; i < sizeA; i++)
	{
		if (i % 2 == 0)
		{
			B[j++] = A[i];
		}
	}
	time.start();
	piramidSort(B, sizeB);
	time.stop();
	cout << "Массив B отсортирован пирамидальной сортировкой:\n";
	printArray(B, sizeB);
	cout << "Сортировка заняла: ";
	time.getTime();
	return 0;
}