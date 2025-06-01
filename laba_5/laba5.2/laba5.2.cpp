#include <iostream>
using namespace std;

enum Emonths
{
	January = 1, February, March,
	April, May, June, July, August, September,
	October, November, December
} months;

int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	int current_month, left;
	cout << "Введите номер текущего месяца (от 1 до 12):";
	cin >> current_month;
	months = December;
	left = (int)months - current_month;
	cout << "\nДо конца года осталось " << left << " месяца(ев)\n";
	return 0;
}