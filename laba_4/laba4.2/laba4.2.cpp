#include <conio.h>
#include <iostream>

using namespace std;

#define DELAY 1280000

void update(struct MyTime* t);

void display(struct MyTime* t);

struct MyTime //структура для хранения времени 
{
	int hours;
	int minutes;
	int seconds;
};

int main(void)
{
	struct MyTime St;
	St.hours = 0;
	St.minutes = 0;
	St.seconds = 0;
		for (;;)
		{
			if (_kbhit())
			{
				update(&St);
				display(&St);
			}
		}
}

void update(struct MyTime* t)
{
	t->seconds++;
	if (t->seconds == 60) 
	{
		t->seconds = 0; t->minutes++;  //если насчитывается 60 секунд, секунды обнуляются, количество минут увеличивается на 1
	}
	if (t->minutes == 60)
	{ 
		t->minutes = 0; t->hours++;  //если насчитывается 60 минут, минут обнуляются, количество часов увеличивается на 1
	}
	if (t->hours == 24) //если насчитывается 24 часа, часы обнуляются
	{
		t->hours = 0;
	}
	for (long int i = 1; i < DELAY; ++i); //создание "задержки", из-за работы цикла 
}

void display(struct MyTime* t)
{
	cout << t->hours << '.' << t->minutes << '.' << t->seconds << endl;
}