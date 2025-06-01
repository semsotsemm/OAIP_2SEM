#include <iostream>
#include <windows.h>

using namespace std;

FILE* fdata;

typedef struct Student
{
	int index;               //Порядковый номер студента
	char fio[100];           // Фамилия, имя, отчество
	int grademat;            // Оценка по вышмату 
	int gradeoaip;           // Оценка по оаип
	int gradeopi;            // Оценка по опи
	int gradebel;            //Оценка по бел язу
} STU;

int get_index()
{
	STU buf;
	int maxIndex = 0;       // Хранит максимальный индекс найденной записи

	if (!fopen_s(&fdata, "data.bin", "rb"))      // Открываем файл для чтения
	{
		while (fread(&buf, sizeof(STU), 1, fdata))      // Проходим по всем записям в файле
		{
			if (buf.index > maxIndex)
			{
				maxIndex = buf.index;    // Обновляем максимальный индекс
			}
		}
		fclose(fdata);

		return maxIndex + 1;    // Возвращаем следующий свободный индекс
	}
	else
	{
		return 1;    // Если файл не открыт - он еще не создан
	}
}

void input(int size)
{
	STU buf;
	for (int i = 0; i < size; i++)
	{
		buf.index = get_index();
		fopen_s(&fdata, "data.bin", "ab");
		cout << "Введите фамилию, имя, отчество гражданина (через пробел):\n";
		cin.ignore();
		cin.getline(buf.fio, 100);
		cout << "Введите оценку студента за экзамен по выш.мату:\n";
		cin >> buf.grademat;
		cout << "Введите оценку студента за экзамен по оаип:\n";
		cin >> buf.gradeoaip;
		cout << "Введите оценку студента за экзамен по опи:\n";
		cin >> buf.gradeopi;
		cout << "Введите оценку студента за экзамен по бел. язу:\n";
		cin >> buf.gradebel;
		fwrite(&buf, sizeof(buf), 1, fdata);
		fclose(fdata);
	}
}

void showlist()
{
	STU buf;
	cout << "   Фио студента: \t\t\t|\tОаип\t|\tОпи\t|\tВыш.мат\t|\tБел.яз\n";
	cout << "____________________________________________________________________________________________________________\n";
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&buf, sizeof(buf), 1, fdata)) // Проверяем успешность чтения
		{
			cout << buf.index << ". " << buf.fio << "\r\t\t\t\t\t|\t" << buf.gradeoaip << "\t|\t" << buf.gradeopi << "\t|\t" << buf.grademat << "\t|\t" << buf.gradebel << endl;
		}
		fclose(fdata);
	}
	else
	{
		cout << "Ошибка открытия файла\n";
	}
}

void getperf(int& quanoaip, int& quanopi, int& quanbel, int& quanmat,int& generalquan)
{
	STU buf;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&buf, sizeof(STU), 1, fdata))      // Проходим по всем записям в файле
		{
			if (buf.gradeoaip >= 4)
			{
				quanoaip++;
			}
			if (buf.gradeopi >= 4)
			{
				quanopi++;
			}
			if (buf.gradebel >= 4)
			{
				quanbel++;
			}
			if (buf.grademat >= 4)
			{
				quanmat++;
			}
			if (buf.gradeoaip >= 4 && buf.gradeopi >= 4 && buf.gradebel >= 4 && buf.grademat >= 4)
			{
				generalquan++;
			}
		}
	}
	else
	{
		cout << "Ошибка открытия файла\n";
	}
	fclose(fdata);
}

void showperf(int& quanoaip, int& quanopi, int& quanbel, int& quanmat, int& generalquan)
{
	double perf;
	int quanstudents = get_index() - 1;
	int userinput;
	cout << "Введите по какому предмету вас интересует успеваемость:\n";
	cout << "1 - Оаип\n" << "2 - Опи\n" << "3 - Выш.мат\n" << "4 - Бел.яз\n" << "5 - Общая успеваемость\n" << "(0 - Для выхода из программы)\n";
	do
	{
		cin >> userinput;
		switch (userinput)
		{
		case 1:
			perf = 100 * quanoaip / quanstudents;
			cout << "Успеваемость студентов по предмету оаип: " << perf << "%\n";
			break;
		case 2:
			perf = 100 * quanopi / quanstudents;
			cout << "Успеваемость студентов по предмету опи: " << perf << "%\n";
			break;
		case 3:
			perf = 100 * quanmat / quanstudents;
			cout << "Успеваемость студентов по предмету выш.мат: " << perf << "%\n";
			break;
		case 4:
			perf = 100 * quanbel / quanstudents;
			cout << "Успеваемость студентов по предмету бел.яз: " << perf << "%\n";
			break;
		case 5:
			perf = 100 * generalquan / quanstudents;
			cout << "Общая успеваемость студентов: " << perf << "%\n";
			break;
		case 0: 
			break;
		default:
			cout << "Ошибка ввода";
			break;
		}
	} while (userinput != 0);
}

int main()
{
	int size, user_output, quanoaip = 0, quanopi = 0, quanbel = 0, quanmat = 0, generalquan = 0;
	setlocale(LC_CTYPE, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Выберите операцию:\n" << "1 - Ввод новой информации\n";
	cout << "2 - Вывод заполненой информации\n" << "3 - Показать сведения об общей успеваемости\n";
	cout << "0 - Для выхода из программы\n";
	do
	{
		cin >> user_output;
		switch (user_output)
		{
		case 1:
			cout << "Введите количество Студентов: ";
			cin >> size;
			input(size);
			break;
		case 2:
			showlist();
			break;
		case 3:
			getperf(quanoaip, quanopi, quanbel, quanmat, generalquan);
			showperf(quanoaip, quanopi, quanbel, quanmat, generalquan);
			break;
		}
		cout << "Что дальше?\n";
	} while (user_output != 0);
}