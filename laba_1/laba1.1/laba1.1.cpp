#include <iostream>
using namespace std;

int f1 (char *s)
{  
	cout << s <<" \nВыполняется тест №1" << endl;
   return 1;
}

int f2 (char *s)
{  
	cout << s<<" \nВыполняется тест №2" << endl;
   return 2;
}

void callfun (char *s, int (*f)(char *))
{  
	cout << " f() = " << f(s) << '\n';
}

int main ()
{ 
   setlocale(0, "Rus");
   callfun((char*)"Тест №1 вызван", f1);
   callfun((char*)"Тест №2 вызван", f2);
}
