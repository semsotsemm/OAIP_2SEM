#pragma once
#include "lists.h"

struct Table
{
    int size;
    Element* hash;
    char (*getSymbol)(void*);
    int (*getKey)(void*);
    int (*getRepeat)(void*);
    void (*addRepeat)(void*);

    Table(int siz, char (*getS)(void*), int (*getK)(void*), int (*getR)(void*), void (*addR)(void*))
    {
        size = siz;
        hash = new Element[siz]; // Создаем массив элементов

        getSymbol = getS;
        getKey = getK;
        getRepeat = getR;
        addRepeat = addR;

        for (int i = 0; i < size; i++)
        {
            hash[i].initialize(getS, getK, getR, addR); // Правильная инициализация
        }
    }

    ~Table()
    {
        delete[] hash;
    }

    void searchBySymbol(int key);
    void addSentence(void* newElement);
    void printTable();
    void printList(Element* firstElement);
};
