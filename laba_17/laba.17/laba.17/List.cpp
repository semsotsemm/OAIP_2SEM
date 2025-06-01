#include "List.h"

Element* Object::GetLast() {
    Element* e = Head;
    if (!e) return nullptr;
    while (e->Next) e = e->Next;
    return e;
}

bool Object::Insert(void* data) {
    Element* e = new Element(nullptr, data, Head);
    if (Head) Head->Prev = e;
    Head = e;
    return true;
}

bool Object::InsertEnd(void* data) {
    if (!Head) {
        Head = new Element(nullptr, data, nullptr);
        return true;
    }
    Element* last = GetLast();
    Element* e = new Element(last, data, nullptr);
    last->Next = e;
    return true;
}

bool Object::Delete(Element* e) {
    if (!e) return false;
    if (e->Prev) e->Prev->Next = e->Next;
    else Head = e->Next;
    if (e->Next) e->Next->Prev = e->Prev;
    delete e;
    return true;
}

bool Object::Delete(void* data) {
    Element* e = Head;
    while (e) {
        if (e->Data == data) {
            Delete(e);
            return true;
        }
        e = e->Next;
    }
    return false;
}

bool Object::DeleteList() {
    Element* e = Head;
    while (e) {
        Element* nxt = e->Next;
        delete e;
        e = nxt;
    }
    Head = nullptr;
    return true;
}

void Object::PrintList(void(*f)(void*)) {
    Element* e = Head;
    while (e) {
        f(e->Data);
        e = e->Next;
    }
}

int Object::CountList() {
    int cnt = 0;
    Element* e = Head;
    while (e) { ++cnt; e = e->Next; }
    return cnt;
}

// Определение Create() находится только здесь, чтобы избежать дублирования
Object Create() {
    return Object();
}