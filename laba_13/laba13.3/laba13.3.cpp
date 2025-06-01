#pragma once

#include "Hash.h"
#include <iostream>

using namespace std;

struct AAA                               // Структура данных AAA для хранения ключа и строки
{
    int key;                             // Ключ элемента
    char* mas;                           // Значение элемента

    AAA(int k, char* z)                  // Конструктор для инициализации ключа и строки
    {
        key = k;
        mas = z;
    }
    AAA() {}                             // Конструктор по умолчанию
};

int key(void* d)                         // Функция для получения ключа из структуры AAA
{
    AAA* f = (AAA*)d;
    return f->key;
}

void AAA_print(void* d)                  // Функция для вывода элемента AAA
{
    cout << " ключ " << ((AAA*)d)->key << " - " << ((AAA*)d)->mas << endl;
}

int main()
{
    setlocale(LC_ALL, "rus");            // Устанавливаем русскую локаль
    int siz = 10, choice, k;
    cout << "Введите размер хеш-таблицы" << endl;
    cin >> siz;
    Object H = create(siz, key);         // Создаем хеш-таблицу
    for (;;)                             // Выводим меню
    {
        cout << "1 - вывод хеш-таблицы" << endl;
        cout << "2 - добавление элемента" << endl;
        cout << "3 - удаление элемента" << endl;
        cout << "4 - поиск элемента" << endl;
        cout << "5 - заполнить хеш-таблицу с случайными ключами" << endl;
        cout << "0 - выход" << endl;
        cout << "сделайте выбор" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0:
            exit(0);                     // Выход из программы
        case 1:
            H.scan(AAA_print);           // Выводим все элементы хеш-таблицы
            break;

        case 2:
        {
            AAA* a = new AAA;
            char* str = new char[20];
            cout << "введите ключ" << endl;
            cin >> k;
            a->key = k;
            cout << "введите строку" << endl;
            cin >> str;
            a->mas = str;

            if (H.N == H.size)
            {
                cout << "Таблица заполнена" << endl;
            }
            else
            {
                H.insert(a);             // Добавление нового элемента в таблицу
            }
        }
        break;

        case 3:
        {
            cout << "введите ключ для удаления" << endl;
            cin >> k;
            H.deleteByKey(k);            // Удаление элемента по ключу
        }
        break;

        case 4:
        {
            cout << "введите ключ для поиска" << endl;
            cin >> k;
            if (H.search(k) == NULL)     // Поиск элемента по ключу
            {
                cout << "Элемент не найден" << endl;
            }
            else
            {
                AAA_print(H.search(k));
            }
            break;
        }
        case 5:
        {
            for (int i = 1; i <= siz; i++)
            {
                AAA* a = new AAA;
                char* str = new char[5]; // 4 символа + '\0'
                strcpy_s(str, 5, "abcd"); // Присваиваем строку "abcd"
                a->key = rand() % 100 + 1; // Генерация случайного ключа
                a->mas = str;

                if (H.N == H.size)
                {
                    cout << "Таблица заполнена" << endl;
                }
                else
                {
                    H.insert(a, a->key);             // Добавление нового элемента в таблицу
                }
            }
        }
        break;
        }
    }
    return 0;
}
