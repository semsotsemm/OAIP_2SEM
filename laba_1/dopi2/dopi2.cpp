#include <iostream>
#include <string>

using namespace std;

void leng(string world) 
{
	int worldleng=0,maxleng=0,i=0;
	while (i < world.length())
	{
		for (; world[i] != ' ' && i < world.length(); i++)
		{
			worldleng++;
		}
		if (maxleng < worldleng)
		{
			maxleng = worldleng;
		}
		worldleng = 0;
		i++;
	}
	cout <<"Количество символов в слове максимальной длинны:" << maxleng;
}

int main()
{
	string world;
	setlocale(LC_CTYPE, "Russian");
	cout << "Введите строку: ";
	getline(cin,world);
	leng(world);
}