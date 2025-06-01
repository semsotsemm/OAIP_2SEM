#include <iostream>

using namespace std;

void swapNumbers(int& number1, int& number2)
{
	int parm = number1;
	number1 = number2;
	number2 = parm;
}

void printCombination(const int* numbers)
{
	for (int i = 0; i < 4; i++)
	{
		cout << numbers[i] << " ";
	}
	cout << "\n";
}

void generatePermutations(int* numbers, int count, int index1, int index2)
{
	swapNumbers(numbers[index1], numbers[index2]);
	if (count % 8 != 0 && count % 8 != 1)
	{
		printCombination(numbers);
	}
	else if (count % 8 == 0)
	{
		swapNumbers(numbers[0], numbers[1]);
	}
	if (count == 32)
	{
		return;
	}
	else if (count % 2 == 0)
	{
		generatePermutations(numbers, count + 1, index1 - 1, index2 - 1);
	}
	else if (count % 2 != 0)
	{
		generatePermutations(numbers, count + 1, index1 + 1, index2 + 1);
	}
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int size = 4, count = 0;
	int* numbers = new int[size];
	for (int i = 0; i < 4; i++)
	{
		cout << "Введите " << i + 1 << " число: ";
		cin >> numbers[i];
	}
	generatePermutations(numbers, count, size - 2, size - 1);
}