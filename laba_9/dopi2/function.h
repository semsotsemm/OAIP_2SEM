struct Student
{
	char secondname[20];
	char name[20];
	char surname[20];
	int yearOfBirth;
	int group;
	int course;
	int oaipGrade;
	int opiGrade;
	int englishGrade;
	int mathemathicsGrade;
	int physicsGrade;
	Student* next;
	Student* previous;
};


void readList();

void showList();

void addStudent();

void printLine();

void calculateAverageScore();

void findYoungest();

void findOldest();

void findTheBestStudent();