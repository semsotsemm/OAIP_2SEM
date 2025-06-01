#pragma once

#include "Hash.h"
#include <iostream>

int HashFunction(int key, int size, int p)     // Функция хеширования
{
    double key2 = 5 * ((0.6180339887499 * key) - int((0.6180339887499 * key)));
    return (p + key) % size;
}

int Next_hash(int hash, int size, int p)       // Функция вычисления следующего хеша (метод пробирования)
{
    return (hash + 7 * p + 2 * p * p) % size;
    // (h'(key) + с1*i+ c2*i^2) mod hashTableSize.
}

Object create(int size, int(*getkey)(void*))   // Функция создания объекта хеш-таблицы
{
    return *(new Object(size, getkey));
}

Object::Object(int size, int(*getkey)(void*))  // Конструктор хеш-таблицы
{
    N = 0;
    this->size = size;
    this->getKey = getkey;
    this->data = new void* [size];
    for (int i = 0; i < size; ++i)
    {
        data[i] = NULL;                        // Инициализация массива NULL-значениями
    }
}

bool Object::insert(void* d)                   // Метод вставки элемента в хеш-таблицу
{
    bool b = false;
    if (N != size)
    {
        for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0); i != size && !b; j = Next_hash(j, size, ++i))
        {
            if (data[j] == NULL || data[j] == DEL) // Вставка в пустую или удаленную ячейку
            {
                data[j] = d;
                N++;
                b = true;
            }
        }
    }
    return b;
}

bool Object::insert(void* d, int a)                   // Метод вставки элемента в хеш-таблицу
{
    bool b = false;
    if (N != size)
    {
        for (int i = 0, t = getKey(d), j = HashFunction(t, size, 0); i != size && !b; j = Next_hash(j, size, ++i))
        {
            if (data[j] == NULL || data[j] == DEL) // Вставка в пустую или удаленную ячейку
            {
                data[j] = d;
                N++;
                b = true;
            }
        }
    }
    return b;
}

int Object::searchInd(int key)                 // Метод поиска индекса элемента по ключу
{
    int t = -1;
    bool b = false;
    if (N != 0)
    {
        for (int i = 0, j = HashFunction(key, size, 0); data[j] != NULL && i != size && !b; j = HashFunction(key, size, ++i))
        {
            if (data[j] != DEL)                // Игнорируем удаленные элементы
            {
                if (getKey(data[j]) == key)    // Найден нужный ключ
                {
                    t = j;
                    b = true;
                }
            }
        }
    }
    return t;
}

void* Object::search(int key)                  // Метод поиска элемента по ключу
{
    int t = searchInd(key);
    return (t >= 0) ? data[t] : NULL;
}

void* Object::deleteByKey(int key)             // Метод удаления элемента по ключу
{
    int i = searchInd(key);
    void* t = data[i];
    if (t != NULL)
    {
        data[i] = DEL;                         // Помечаем ячейку как удаленную
        N--;
    }
    return t;
}

bool Object::deleteByValue(void* d)            // Метод удаления элемента по значению
{
    return (deleteByKey(getKey(d)) != NULL);
}

void Object::scan(void(*f)(void*))             // Метод обхода элементов и вывода их состояния
{
    for (int i = 0; i < this->size; i++)
    {
        std::cout << " Элемент " << i;
        if ((this->data)[i] == NULL)
        {
            std::cout << "  пусто" << std::endl;
        }
        else
        {
            if ((this->data)[i] == DEL)
            {
                std::cout << "  удален" << std::endl;
            }
            else
            {
                f((this->data)[i]);            // Вывод значения элемента
            }
        }
    }
}
