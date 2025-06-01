#include <iostream>

using namespace std;

void sum(int** A,int size) 
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i==j && j != 0)
			{
				for (int k = j-1; k >= 0; k--)
				{
					sum += A[i][k];
				}
			}
		}
	}
	cout << "Сумма элементов стоящих ниже главной диагонали = " << sum;
}

int main()
{
	int size;
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите размер матрицы: ";
	cin >> size;
	cout << "Ваша матрица:\n";
	srand((unsigned)time(NULL));
	int **A = new int* [size];
	for (int i = 0; i < size; i++)
	{
		A[i] = new int[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			A[i][j] = rand() % 20; //Заполняет матрицу случайными числами от 0 до 20
			cout << A[i][j]<<'\t'; //Выводит матрицу
		}
		cout << endl;
	}
	sum(A,size);
	for (int i = 0; i < size; i++)
	{
		delete A[i];
	}
	delete A;
	return 0;
}