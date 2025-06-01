#include <iostream>

using namespace std;

int checkOverflow(const int a, const int maxNumber, int& discharge, int combination, int overflow)
{
	int num = 0;
	if (overflow % 10 != a)
	{
		return combination;
	}
	else 
	{
		discharge++;
		overflow /= 10;
		checkOverflow(a, maxNumber, discharge, combination, overflow);
	}
	for (int i = 0; i < discharge; i++)
	{
		num += pow(10, i);
	}
	combination += pow(10, discharge) - a * num - 1;
	return combination;
}

int main()
{
	FILE* fdata;
	setlocale(LC_CTYPE, "Russian");
	int a, maxNumber = 0, combination = 0, discharge = 0, overflow;
	cout << "Введите число A: ";
	cin >> a;
	for (int i = 0; i < a; i++)
	{
		maxNumber += pow(10, i);
	}
	maxNumber *= a;
	if (!fopen_s(&fdata, "data.txt", "w"))
	{
		while (combination <= maxNumber)
		{
			overflow = combination;
			fprintf(fdata,"%d ", combination);
			combination = checkOverflow(a, maxNumber, discharge, combination, overflow);
			combination++;
			discharge = 0;
		}
		fclose(fdata);
		cout << "Комбинации успешно записаны\n";
	}
	else 
	{
		cout << "Ошибка открытия файла\n";
	}
	return 0;
}