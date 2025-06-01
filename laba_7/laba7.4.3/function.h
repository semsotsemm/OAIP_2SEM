struct stack
{
	int value;
	stack* next;
	stack* prev;
};

void pushNewElement(stack*& head);
void popElement(stack*& head);
void printStack(stack* head);
void clear(stack*& head);
void popPositiveElement(stack*& head);
void pushStackToFile(stack* head);
void getStackFromFile(stack*& head);