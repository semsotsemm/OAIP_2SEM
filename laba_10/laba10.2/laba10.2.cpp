#include <iostream>

char s[100];

void main()
{
	setlocale(LC_CTYPE, "Russian");
	bool isPalindrom = true;
	printf("\nВведите строку: ");
	gets_s(s);
	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i]==s[strlen(s) - 1 - i])
		{
			continue;
		}
		else
		{
		  isPalindrom = false;
		}
	}
	if (isPalindrom)
	{
		printf("Строка - палиндром");
	}
	else
	{
		printf("Строка - не палиндром");
	}
}