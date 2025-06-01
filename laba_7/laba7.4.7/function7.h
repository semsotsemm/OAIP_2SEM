struct numbers 
{
	int value;
	numbers* next;
};

void pushNewElement(numbers*& head);
void popElement(numbers*& head);
void printList(numbers* head);
void clear(numbers*& head);
void pushListToFile(numbers* head);
void getListFromFile(numbers*& head);
void popElementMoreHundred(numbers*& head);