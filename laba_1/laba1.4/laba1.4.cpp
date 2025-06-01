#include <iostream>

using namespace std;

void deh(double &a, double &b, const double step) 
{
    a += step;
    b += step;
}
double f(const double x) 
{
    double y;
    y = sin(x) + 0.1;
    return y;
}

int main()
{
    double b,a,step=0.001;
    char plus = '+';
    setlocale(LC_CTYPE,"Russian");
    cout << "Введите приближенное значение корня: ";
    cin >> a;
    b = a + step;
    do
    {
        while (f(a) * f(b) > 0)
        {
            deh(a, b, step);
        }
        cout << "Корень уравнения: " << a;
        cout << "\nВведите + чтобы посчитать следующий корень, - для выхода из программы ";
        cin >> plus;
        deh(a, b, step);
    } while (plus != '-');
    return 0;
}