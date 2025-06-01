#include <iostream>

using namespace std;

int countConflicts(int* groups, int** countries, int n) {
    int conflicts = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) { 
            if (countries[i][j] == 1 && groups[i] != groups[j]) {
                conflicts++;
            }
        }
    }
    return conflicts;
}
//0110 1011 1101 0110
void generateGroups(int* groups, int** countries, int n) {
    for (int i = 0; i < n; i++) {
        groups[i] = -1;
    }
    groups[0] = 0;
    for (int i = 1; i < n; i++) {
        int conflictsA = 0, conflictsB = 1; 
        for (int j = 0; j < i; j++) {
            if (countries[i][j] == 1) {
                if (groups[j] == 0) conflictsA++;
                if (groups[j] == 1) conflictsB++;
            }
        }
        groups[i] = (conflictsA <= conflictsB) ? 0 : 1;
    }
}

int main() {
    int n;
    setlocale(LC_CTYPE, "Russian");
    cout << "Введите количество стран: ";
    cin >> n;
    int** countries = new int* [n];
    int* groups = new int[n]; 
    for (int i = 0; i < n; i++) {
        countries[i] = new int[n];
    }
    cout << "Введите матрицу смежности (симметричную относительно главной диагонали):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> countries[i][j];
        }
    }
    cout << "\nВаша матрица смежности:\n  ";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < n; j++) {
            cout << countries[i][j] << " ";
        }
        cout << "\n";
    }
    generateGroups(groups, countries, n);
    int minConflicts = countConflicts(groups, countries, n);
    cout << "Минимальное количество конфликтов: " << minConflicts << "\n";
    cout << "Группа A: ";
    for (int i = 0; i < n; i++) {
        if (groups[i] == 0) {
            cout << i + 1 << " ";
        }
    }
    cout << "\nГруппа Б: ";
    for (int i = 0; i < n; i++) {
        if (groups[i] == 1) {
            cout << i + 1 << " ";
        }
    }
    cout << "\n";
    for (int i = 0; i < n; i++) {
        delete[] countries[i];
    }
    delete[] countries;
    delete[] groups;

    return 0;
}