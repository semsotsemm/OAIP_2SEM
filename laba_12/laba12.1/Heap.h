#pragma once

struct AAA // ��������� AAA - �������� �������� x � ����� print
{
    int x;
    void print();
};

namespace heap // ������������ ���� heap
{
    enum CMP // ������������ CMP ��� �������� ��������� ����������� ���������
    {
        LESS = -1, EQUAL = 0, GREAT = 1
    };

    struct Heap // ��������� Heap - ���������� �������� ����
    {
        int size;    // ������� ������ ����
        int maxSize; // ������������ ������ ����
        void** storage; // ������ ���������� �� ������
        CMP(*compare)(void*, void*); // ������� ��������� ���������
        Heap(int maxsize, CMP(*f)(void*, void*))      // ����������� ����
        {
            size = 0;
            storage = new void* [maxSize = maxsize];
            compare = f;
        };
        int left(int ix);   // ������ ������ �������
        int right(int ix);  // ������ ������� �������
        int parent(int ix); // ������ ��������
        bool isFull() const   // �������� �� �������������
        { 
            return (size >= maxSize);
        }
        bool isEmpty() const  // �������� �� �������
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
        void swap(int i, int j); // ����� ���������
        void heapify(int ix);    // ����������� ����
        void insert(void* x);    // ������� ��������
        void* extractMax();      // ���������� ������������� ��������
        void* extractMin();      // ���������� ������������ ��������
        void* extractI();         // ����������� I-�� �������� 
        void unionHeap(Heap h2);         //���������� 2 ��� � ����
        void scan(int i) const;  // ����� ���� �� �����
    };

    Heap create(int maxsize, CMP(*f)(void*, void*)); // ������� �������� ����
};