struct List
{
	void* value;

	int (*getKey)(void*);

	List* head;
	List* next;
	List* prev;

	List()
	{
		next = nullptr;
		prev = nullptr;
		head = nullptr;
	}

	bool insertElement(void* data);
	void printList();
	void* foundInList(int value);
	bool deleteFromList(int value);
	void printListIntoFile();

	void initialize(int (*getK)(void*))
	{
		getKey = getK;
	}
};