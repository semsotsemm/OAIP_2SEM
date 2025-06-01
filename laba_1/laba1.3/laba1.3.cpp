#include <iostream>

int sum(int size, long long int n, ...);

using namespace std;

int main()
{
	cout << sum(6, 4, 5, 1, 2, 3, 0) << std::endl;
	cout << sum(2, 34, 4445);
	return 0;
}

int sum(int size, long long int n, ...)
{
	long long int* p = &n;
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += *(p++);
	return sum;
}