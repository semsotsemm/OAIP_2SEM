#include <iostream>

using namespace std;

int fmin(int size, long long int n, ...)
{
	long long int* p = &n;
	int min = 1000;
	for (int i = 0; i < size; i++)
	{
		if (*(p) < min)
		{
			min = *(p);
		}
		p++;
	}
	return min;
}

int main()
{
	setlocale(LC_CTYPE,"Russian");
	cout << "Минимальное из чисел int: " << fmin(5,62,44,63,100,3);
	return 0;
}