#include <iostream>
#include "Hash_Table.h"

using namespace std;

struct Words 
{
	int key;
	string word;
	string prompt;
};

void printLine() 
{
	cout << "___________________________\n";
}

int getKey(void* element)
{
	Words* data = (Words*)element;
	return data->key;
}

string getWord(void* element)
{
	Words* data = (Words*)element;
	return data->word;
}

string getPrompt(void* element)
{
	Words* data = (Words*)element;
	return data->prompt;
}

int main()
{
	int size, userInput;
	setlocale(LC_CTYPE,"Russian");
	cout << "Введите размер хеш-таблицы: ";
	cin >> size;
	Table* firstTable = new Table(size, getKey, getWord, getPrompt);
	while (true)
	{
		printLine();
		cout << "Меню:\n";
		cout << "1 - Ввести новое зарезервированное слово\n";
		cout << "2 - Вывести хеш-таблицу зарезервированных слов\n";
		cout << "3 - Получить подсказку по слову\n";
		cout << "4 - Заполнить хеш-таблицу из файла\n";
		cout << "5 - Записать таблицу в файл\n ";
		cout << "0 - Выход из программы\n";
		printLine();
		cin >> userInput;
		switch (userInput)
		{
		case 1: 
		{
			Words* newWords = new Words;
			int sum = 0;
			cout << "Введите зарезервированное слово: ";
			cin >> newWords->word;
			cout << "Введите подсказку: ";
			cin >> newWords->prompt;
			for (int i = 0; i < newWords->word.length(); i++)
			{
				sum += newWords->word[i];
			}
			newWords->key = sum;
			firstTable->insertInTable(newWords);
			break;
		}
		case 2:
			firstTable->printTable();
			break;
		case 3:
		{
			cout << "Введите слово, подсказку к которому хотите получить: ";
			string searchedWord;
			cin >> searchedWord;
			int sum = 0;
			for (int i = 0; i < searchedWord.length(); i++)
			{
				sum += searchedWord[i];
			}
			firstTable->searchWordByKey(sum);
			break;
		}
		case 4: 
		{
			char fileName[40];
			cout << "Введите название файла: ";
			cin.ignore();
			scanf_s("%s", fileName);
			FILE* file;
			fopen_s(&file, fileName, "r");
			if (file == NULL) 
			{
				cout << "Не удалось открыть файл" << fileName;
			}
			char line[256];
			while (fgets(line, sizeof(line), file)) 
			{
				for (int i = 0; i < sizeof(line); i++)
				{

				}
			}
			break;
		}
		case 0:
			exit(0);
			break;
		default: 
			cout << "Ошибка ввода\n";
			break;
		}
	}
}