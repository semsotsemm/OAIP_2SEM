#include "Heap.h"
#include <iostream>
#include <iomanip>

void AAA::print()
{
    std::cout << x; // Вывод значения x
}

namespace heap
{
    Heap create(int maxsize, CMP(*f)(void*, void*))
    {
        return *(new Heap(maxsize, f)); // Создаем и возвращаем новую кучу
    }

    int Heap::left(int ix)
    { 
        return (2 * ix + 1 >= size) ? -1 : (2 * ix + 1);  //по формуле 2i + 1 возвращаем левый элемент бинарной кучи если она меньше максимального размера или -1
    }
    int Heap::right(int ix)
    {
        return (2 * ix + 2 >= size) ? -1 : (2 * ix + 2); //по формуле 2i + 2 возвращаем правый элемент бинарной кучи если она меньше максимального размера или -1
    }
    int Heap::parent(int ix)
    {
        return (ix + 1) / 2 - 1;  //по формуле (i+1)/2 -1 возвращаем родителя для i-ого элемента 
    }

    void Heap::swap(int i, int j)
    {
        void* buf = storage[i];
        storage[i] = storage[j];
        storage[j] = buf;
    }

    void Heap::heapify(int ix)
    {
        int l = left(ix), r = right(ix), irl = ix;
        if (l > 0)
        {
            if (isGreat(storage[l], storage[ix]))
            {
                irl = l;
            }
            if (r > 0 && isGreat(storage[r], storage[irl]))
            {
                irl = r;
            }
            if (irl != ix)
            {
                swap(ix, irl);
                heapify(irl);
            }
        }
    }

    void Heap::insert(void* x)
    {
        int i;
        if (!isFull())
        {
            storage[i = ++size - 1] = x;
            while (i > 0 && isLess(storage[parent(i)], storage[i]))
            {
                swap(parent(i), i);
                i = parent(i);
            }
        }
    }

    int Heap::getMinIndex() {
        int minIndex = 0;
        for (int i = 1; i < size; i++) 
        {
            if (isLess(storage[i], storage[minIndex])) 
            {
                minIndex = i;
            }
        }
        return minIndex;
    }

    void* Heap::extractMax()
    {
        void* rc = nullptr;
        if (!isEmpty())
        {
            rc = storage[0];
            storage[0] = storage[size - 1];
            size--;
            heapify(0);
        }
        return rc;
    }

    void* Heap::extractMin()
    {
        void* rc = nullptr;
        if (!isEmpty())
        {
            rc = storage[getMinIndex()];
            storage[getMinIndex()] = storage[size - 1];
            size--;
            heapify(0);
        }
        return rc;
    }

    void* Heap::extractI()
    {
        int index;
        void* rc = nullptr;
        std::cout << "Введите индекс элемента который хотите удалить: ";
        std::cin >> index;
        if (!isEmpty())
        {
            rc = storage[index];
            storage[index] = storage[size - 1];
            size--;
            heapify(0);
        }
        return rc;
    }

    void Heap::unionHeap(Heap h2)
    {
        for (int i = 0; i < h2.size; i++)
        {
#define A1 ((AAA*)h2.storage[i])
            insert(A1);
            heapify(0);
#undef A1 
        }
    }

    void Heap::scan(int i) const
    {
        int probel = 20;
        std::cout << '\n';
        if (size == 0) std::cout << "Куча пуста";
        for (int u = 0, y = 0; u < size; u++)
        {
            std::cout << std::setw(probel + 10) << std::setfill(' ');
            ((AAA*)storage[u])->print();
            if (u == y)
            {
                std::cout << '\n';
                y = (y == 0) ? 2 : y + y * 2;
            }
            probel /= 2;
        }
        std::cout << '\n';
    }
}
