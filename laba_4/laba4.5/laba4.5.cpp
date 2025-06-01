#include <iostream>
#include <windows.h>

using namespace std;

FILE* fdata;

typedef struct Human
{
	int index;
	char fio[100];           // Фамилия, имя, отчество
	int year_of_birth;       // Год рождения
	char address[200];       // Адрес 
	char gender[2];          // Пол
} PERSON;

int get_index()
{
	PERSON buf;
	int maxIndex = 0;       // Хранит максимальный индекс найденной записи

	if (!fopen_s(&fdata, "data.bin", "rb"))      // Открываем файл для чтения
	{
		while (fread(&buf, sizeof(PERSON), 1, fdata))      // Проходим по всем записям в файле
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
	PERSON buf;
	for (int i = 0; i < size; i++)
	{
		buf.index = get_index();
		fopen_s(&fdata, "data.bin", "ab");
		cout << "Введите фамилию, имя, отчество гражданина (через пробел):\n";
		cin.ignore();
		cin.getline(buf.fio, 100);
		cout << "Введите год рождения гражданина:\n";
		cin >> buf.year_of_birth;
		cout << "Введите адрес гражданина:\n";
		cin.ignore();
		cin.getline(buf.address, 200);
		cout << "Введите пол гражданина (м или ж):\n";
		cin >> buf.gender;
		fwrite(&buf, sizeof(buf), 1, fdata);
		fclose(fdata);
	}
}

void showlist()
{
	PERSON buf;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&buf, sizeof(buf), 1, fdata)) // Проверяем успешность чтения
		{
			cout << buf.index << ". " << buf.fio << "\t\t" << buf.year_of_birth << "\t\t" << buf.address << "   \t" << buf.gender << endl;
		}
		fclose(fdata);
	}
	else
	{
		cout << "Ошибка открытия файла\n";
	}
}

void del()
{
	int index; // Индекс записи для удаления
	cout << "Введите индекс человека, которого хотите удалить из списка: ";
	cin >> index;

	PERSON buf;

	if (fopen_s(&fdata, "data.bin", "rb")) // Открываем исходный файл для чтения
	{
		cout << "Ошибка открытия файла для чтения!\n";
		return;
	}

	FILE* tempFile; // Временный файл для перезаписи
	if (fopen_s(&tempFile, "temp.bin", "wb"))
	{
		cout << "Ошибка создания временного файла!\n";
		fclose(fdata);
		return;
	}

	bool found = false;      // Флаг, что запись найдена
	int newIndex = 1;        // Новый индекс для переиндексации

	while (fread(&buf, sizeof(PERSON), 1, fdata)) // Чтение всех записей из исходного файла и запись в новый файл
	{
		if (buf.index == index)
		{
			found = true; // Пропускаем удаляемую запись
			continue;
		}
		buf.index = newIndex++; // Обновляем индекс для оставшихся записей
		fwrite(&buf, sizeof(PERSON), 1, tempFile);
	}

	fclose(fdata);
	fclose(tempFile);

	remove("data.bin"); // Заменяем исходный файл временным
	rename("temp.bin", "data.bin");

	if (found)
	{
		cout << "Запись с индексом " << index << " успешно удалена.\n";
	}
	else
	{
		cout << "Запись с индексом " << index << " не найдена.\n";
	}
}

void find()
{
	cout << "Введите год рождения ";
	int year;
	cin >> year;
	PERSON buf;
	if (!fopen_s(&fdata, "data.bin", "rb"))
	{
		while (fread(&buf, sizeof(buf), 1, fdata)) // Проверяем успешность чтения
		{
			if (year == buf.year_of_birth)
			{
				cout << "==========================\nФамилия: " << buf.fio << "\nГод рождения: " << buf.year_of_birth
				<< "\nАдрес: " << buf.address << "\nПол: " << buf.gender << "\nИндекс в сипске: " << buf.index << "\n==========================\n";
			}
		}
		fclose(fdata);
	}
	else
	{
		cout << "Ошибка открытия файла\n";
	}
}

int main()
{
	int size, user_output;
	setlocale(LC_CTYPE, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Выберите операцию:\n" << "1 - Ввод новой информации\n";
	cout << "2 - Вывод заполненой информации\n" << "3 - Удаление информации\n";
	cout << "4 - Поиск по году рождения\n";
	do
	{
		cin >> user_output;
		switch (user_output)
		{
		case 1:
			cout << "Введите количество новых жителей города: ";
			cin >> size;
			input(size);
			break;
		case 2:
			showlist();
			break;
		case 3:
			del();
			break;
		case 4:
			find();
			break;
		}
		cout << "Что дальше?\n";
	} while (user_output != 0);
}