#pragma once

struct AAA // Структура AAA - содержит значение x и метод print
{
    int x;
    void print();
};

namespace heap // Пространство имен heap
{
    enum CMP // Перечисление CMP для хранения возможных результатов сравнения
    {
        LESS = -1, EQUAL = 0, GREAT = 1
    };

    struct Heap // Структура Heap - реализация бинарной кучи
    {
        int size;    // Текущий размер кучи
        int maxSize; // Максимальный размер кучи
        void** storage; // Массив указателей на данные
        CMP(*compare)(void*, void*); // Функция сравнения элементов
        Heap(int maxsize, CMP(*f)(void*, void*))      // Конструктор кучи
        {
            size = 0;
            storage = new void* [maxSize = maxsize];
            compare = f;
        };
        int left(int ix);   // Индекс левого потомка
        int right(int ix);  // Индекс правого потомка
        int parent(int ix); // Индекс родителя
        bool isFull() const   // Проверка на заполненность
        { 
            return (size >= maxSize);
        }
        bool isEmpty() const  // Проверка на пустоту
        { 
            return (size <= 0);
        }
        bool isLess(void* x1, void* x2) const 
        { 
            return compare(x1, x2) == LESS; 
        }
        bool isGreat(void* x1, void* x2) const 
        { 
            return compare(x1, x2) == GREAT;
        }
        bool isEqual(void* x1, void* x2) const 
        { 
            return compare(x1, x2) == EQUAL; 
        }
        int getMinIndex();
        void swap(int i, int j); // Обмен элементов
        void heapify(int ix);    // Просеивание вниз
        void insert(void* x);    // Вставка элемента
        void* extractMax();      // Извлечение максимального элемента
        void* extractMin();      // Извлечение минимального элемента
        void* extractI();         // Извелечение I-го элемента 
        void unionHeap(Heap h2);         //Объедиение 2 куч в одну
        void scan(int i) const;  // Вывод кучи на экран
    };

    Heap create(int maxsize, CMP(*f)(void*, void*)); // Функция создания кучи
};