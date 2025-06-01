#include <iostream>
#include <math.h>

using namespace std;

double root(int n, int i)
{
	double underRoot;
	i++;
	if (i != n)
	{
		underRoot = 1 + (n + i) * root(n, i);
	}
	else
	{
		underRoot = 1 + n + i;
	}
	return sqrt(underRoot);
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int i = 0, n;
	double result;
	cout << "Введите число n: ";
	cin >> n;
	result = root(n, i);
	cout << "Результат = " << result;
	return 0;
}