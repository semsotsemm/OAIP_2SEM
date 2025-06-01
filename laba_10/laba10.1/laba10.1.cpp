#include <stdio.h>
#include <iostream>

using namespace std;

void binPrn(unsigned num, int& i)
{
    i++;
    if (num / 2)
    {
        binPrn(num / 2, i);
    }
    putchar(num % 2 + '0');
}

int main(void)
{
    setlocale(LC_CTYPE,"Russian");
    int c, i = 0;
    while (1)
    {
        printf("Number: ");
        if (scanf_s("%d", &c) != 1 || !c) 
        {
            break;
        }
        binPrn(c, i);
        cout << "\nФункция binPrn вызвала себя " << i << " раз\n";
        i = 0;
        putchar('\n');
    }
    return 0;
}