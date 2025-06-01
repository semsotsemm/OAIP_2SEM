#ifndef LIST_H
#define LIST_H

#include <iostream>

struct Element {
    Element* Prev;
    Element* Next;
    void* Data;
    Element(Element* prev, void* data, Element* next)
        : Prev(prev), Next(next), Data(data) {}
};

struct Object {
    Element* Head;
    Object() : Head(nullptr) {}
    Element* GetFirst() { return Head; }
    Element* GetLast();
    bool Insert(void* data);
    bool InsertEnd(void* data);
    bool Delete(Element* e);
    bool Delete(void* data);
    bool DeleteList();
    void PrintList(void(*f)(void*));
    int CountList();
};

// функция создания нового объекта списка
Object Create();

#endif // LIST_H