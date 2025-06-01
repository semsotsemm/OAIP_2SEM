#pragma once
#define HASHDEL (void*) -1                       // Значение для удаленных элементов хеш-таблицы
struct Object                                    // Структура Object, реализующая хеш-таблицу
{
    void** data;                                 // Указатель на массив данных
    int size;                                    // Размер таблицы
    int N;                                       // Количество элементов в таблице
    int(*getKey)(void*);                         // Функция для получения ключа из данных
    Object(int, int(*)(void*));                  // Конструктор объекта
    bool insert(void*);                          // Метод вставки элемента в таблицу
    bool insert(void*, int a);                          // Метод вставки элемента в таблицу
    int searchInd(int key);                      // Метод поиска индекса элемента по ключу
    void* search(int key);
    void* deleteByKey(int key);                  // Метод удаления элемента по ключу
    bool deleteByValue(void*);                   // Метод удаления элемента по значению
    void scan(void(*f)(void*));                  // Метод для вывода хеш-таблицы
};
static void* DEL = (void*)HASHDEL;               // Указатель на специальное значение для удаления
Object create(int size, int(*getkey)(void*));    // Функция создания объекта хеш-таблицы
#undef HASHDEL                                   // Удаляем макрос