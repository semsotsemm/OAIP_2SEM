#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int m = 0, number = 0, pr = 0;
	long fsize;
	char pd;
	FILE* fd;
	errno_t err;
	err = fopen_s(&fd, "b.txt", "r");
	if (err != 0)
	{
		perror("ошибка открытия b.txt");
		return 0;
	}
	fseek(fd, 0L, SEEK_END);
	fsize = ftell(fd);
	fseek(fd, 0L, SEEK_SET);
	printf("Введите номер предложения ");
	cin >> number;
	for (int k = 0; k < fsize; k++)
	{
		fread((void*)&pd, sizeof(char), 1, fd);
		if (pd == '.')   pr++;
		if ((number - 1) == pr)  m++;
		if (number == pr)
		{
			fseek(fd, 0L, SEEK_SET);
			printf("Предложение до %d-ого и %d-ое: ", number, number);
			for (int i = 0; i <= k; i++)
			{
				fread((void*)&pd, sizeof(char), 1, fd);
				printf("%c", pd);
			}
			break;
		}
	}
	if (number > pr)
		printf("Такого номера нет");
	fclose(fd);
	return 0;
}