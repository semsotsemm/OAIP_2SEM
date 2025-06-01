#include <iostream>   
#include <stdio.h>    
using namespace std;

int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	FILE* fp;
	errno_t err;
	char const* st = "привет";
	char* strok = new char [strlen(st) + 1];
	err = fopen_s(&fp, "a.txt", "w");
	if (err != 0)
	{
		perror("ошибка открытия a.txt");
		return EXIT_FAILURE;
	}
	fwrite(st, strlen(st), 1, fp);
	printf("Записан элемент:\n");
	fclose(fp);
	err = fopen_s(&fp, "a.txt", "r");
	if (err != 0)
	{
		perror("ошибка открытия a.txt");
		return EXIT_FAILURE;
	}
	fread(strok, strlen(st), 1, fp);
	strok[strlen(st)] = '\0';
	cout << strok;
	return 0;
}