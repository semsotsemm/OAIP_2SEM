#include <iostream>

using namespace std;

//6+0 5+1 4+2 4+1+1 3+2+1 3+1+1+1 2+2+1+1 2+1+1+1+1 1+1+1+1+1+1

void countCombinations(int m, int n, int& x, int sum) 
{
	if (m > 1)
	{
		if (m + n != sum)
		{
			cout << m << "+" << n;
			for (int i = 0; sum != m + n + i; i++)
			{
				cout << "+1";
			}
			cout << ", ";
		}
		else
		{
			cout << m << "+" << n << ", ";
		}
		if (n > 1)
		{
			n--;
		}
		else
		{
			n++;
			m--;
		}
		x++;
		countCombinations(m, n, x,sum);
	}
}

int main()
{
	setlocale(LC_CTYPE,"Russian");
	int m, n = 0,x = 1, sum;
	cout << "Введите число m: ";
	cin >> m;
	sum = m;
	countCombinations(m, n, x, sum);
	cout << "1";
	for (int i = 1; i < sum; i++)
	{
		cout << "+1";
	}
	cout << "\nС вашим числом можно собрать " << x << " комбинаций натуральных чисел\n";
}