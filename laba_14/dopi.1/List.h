struct element
{
	element* head;
	void* data;
	element* next;
	element* prev;
	element()
	{
		data = nullptr;
		prev = nullptr;
		next = nullptr;
		head = nullptr;
	}
	void insertInList(void* data, element* firstel);
	element* getNextElement(element* ptrEl);
	void deleteElementFromList(element* ptrEl);
};