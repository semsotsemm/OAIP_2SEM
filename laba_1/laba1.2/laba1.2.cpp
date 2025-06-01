#include <iostream> 
double metodPr(double(*)(double), double, double, double);    //прототип
double f(double);     //прототип

int main()
{
	double z;
	z = metodPr(f, 0.0, 2.0, 0.01);
	std::cout << "Result1 = " << z;
}

double metodPr(double (*fun)(double), double a, double b, double h)
{
	double x, s = 0.0;
	x = a + h;
	while (x <= b)
	{
		s += h * fun(x);
		x = x + h;
	}
	return s / 2;
}

double f(double x)
{
	return (2 * x + 5);
}
