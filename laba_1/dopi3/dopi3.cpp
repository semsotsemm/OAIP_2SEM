#include <iostream>

using namespace std;

int kvadr(int intsize)
{
	int col = 0;
	for (int i = 1; i*i < intsize; i++)
	{
		col++;
	}
	return col;
}

int main()
{
	int intsize,col;
	setlocale(LC_CTYPE,"Russian");
	cout << "Введите максимальное значение int: ";
	cin >> intsize;
	col = kvadr(intsize);
	cout << "Количество полных квадратов в int: " << col;
}