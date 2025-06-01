#pragma once

struct Element
{
    Element* head;
    Element* next;
    Element* prev;
    void* data;
    char (*getSymbol)(void*);
    int (*getKey)(void*);
    int (*getRepeat)(void*);
    void (*addRepeat)(void*);

    Element() // Конструктор по умолчанию
    {
        head = nullptr;
        next = nullptr;
        prev = nullptr;
        data = nullptr;
        getSymbol = nullptr;
        getKey = nullptr;
        getRepeat = nullptr;
        addRepeat = nullptr;
    }

    void initialize(char (*getS)(void*), int (*getK)(void*), int (*getR)(void*), void (*addR)(void*)) // Метод инициализации
    {
        getSymbol = getS;
        getKey = getK;
        getRepeat = getR;
        addRepeat = addR;
    }

    void searchInList(Element* firstElement, int key);
    void addToList(Element* firstEl, Element* newEl);
    Element* getNextElement(Element* el);
};
