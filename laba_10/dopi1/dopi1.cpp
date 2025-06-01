#include <iostream>

using namespace std;

int checkOverflow(int num, int a, int& i)
{
	if (num % 10 == a)
	{
		i++;
		checkOverflow(num/10, a, i);
	}
	num += pow(10,i) * (10 - a) - a * i;
	return num;
}

void getCombination(const int upperLimit, int num, int& a, FILE* fdata) 
{
	int i = -1;
	if (num <= upperLimit)
	{
		fprintf(fdata, "%d ", num);
		cout << num << " ";
		if (num % 10 == a)
		{
			num = checkOverflow(num, a, i);
			i = -1;
		}
		else
		{
			num++;
		}
		getCombination(upperLimit, num, a, fdata);
	}
}

int main()
{
	FILE* fdata;
	int a, upperLimit = 0, num = 0, j = 0;
	setlocale(LC_CTYPE,"Russian");
	cout << "Введите число А: ";
	cin >> a;
	for (int i = 0; i < a; i++)
	{
		upperLimit += pow(10,i);
	}
	upperLimit *= a;
	cout << "Числа записанные в файл:\n";
	if (!fopen_s(&fdata, "data.txt", "w"))
	{
		getCombination(upperLimit, num, a, fdata);
	}
	else
	{
		cout << "Ошибка открытия файла\n";
	}
	return 0;
}