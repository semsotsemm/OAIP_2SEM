#include <iostream>

using namespace std;

void swapnum(int& parm1, int& parm2) 
{
    int parm3;
    parm3 = parm2;
    parm2 = parm1;
    parm1 = parm3;
}

void printCombinations(int n[], int start, int size, int& count)
{
    if (start == size) 
    {
        for (int i = 0; i < size; i++)
        {
            cout << n[i] << " ";
        }
        cout << endl;
        count++;
        return;
    }

    for (int i = start; i < size; i++) 
    {
        swapnum(n[start], n[i]);
        printCombinations(n, start + 1, size, count);
        swapnum(n[start], n[i]);
    }
}

int main() 
{
    int n[5];
    int count = 0;
    setlocale(LC_CTYPE, "Russian");
    for (int i = 0; i < 5; i++)
    {
        cout << "Введите " << i + 1 << " число: ";
        cin >> n[i];
    }
    cout << "Все перестановки введенных чисел:" << endl;
    printCombinations(n, 0, 5, count);
    cout << "Всего перестановок: " << count << endl;
    return 0;
}