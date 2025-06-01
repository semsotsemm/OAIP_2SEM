#include <iostream>

#define MAX 100

int* p;               // указатель на область свободной памяти 
int* tos, * bos;      // указатель на вершину и дно стека 
void push(int i);     //прототип
int pop(void);        //прототип 

int main()
{
	setlocale(LC_CTYPE, "Russian");
	int a, b;
	char s[80];
	p = new int[MAX * sizeof(int)];
	if (!p)
	{
		printf("Ошибка при выделении памяти\n");
		exit(1);
	}
	tos = p;
	bos = p + MAX - 1;
	printf("Калькулятор \n Для выхода нажать 'q'\n");
	do
	{
		printf(": ");
		gets_s(s); //ввод первого числа, второго и знака операции

		switch (*s)
		{
		case '+': 
			a = pop(); 
			b = pop();   //сложение
			printf("%d\n", a + b);
			push(a + b); 
			break;
		case '-': 
			a = pop(); 
			b = pop();   //вычитание
			printf("%d\n", b - a);
			push(b - a); 
			break;
		case '*': 
			a = pop();
			b = pop();   //умножение
			printf("%d\n", b * a);
			push(b * a);  
			break;
		case '/':
			a = pop();
			b = pop();   //деление
			if (a == 0) { printf("Деление на 0\n"); break; }
			printf("%d\n", b / a);
			push(b / a);
			break;
		case '.': 
			a = pop();
			push(a); //вывод вершины стека
			printf("Текущее значение на вершине стека: %d\n", a);
			break;
		default:  
			push(atoi(s)); //конвертация из символа в число
			break;
		}
	} while (*s != 'q');
	return 0;
}

void push(int i)     // Занесение элемента в стек
{
	if (p > bos) 
	{
		printf("Стек полон\n"); 
		return;
	}
	*p = i;
	p++;
}

int pop()        // Получение верхнего элемента из стека
{
	p--;
	if (p < tos) 
	{
		printf("Стек пуст\n");
		return 0;
	}
	return *p;
}