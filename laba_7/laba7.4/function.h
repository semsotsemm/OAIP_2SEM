struct stack
{
	int value;
	stack* next;
};

void inputToStack(stack*& first);

void delFromStack(stack*& first);

bool isStackEmpty(stack* first);

void showList(stack* first);

void inputStackToFile(stack* first);

void readFromFile(stack*& first);

void clear(stack*& first);

void buildNewStack(stack* first);