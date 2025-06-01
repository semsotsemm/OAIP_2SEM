#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

FILE* fdata, * fnewdata;

struct Voucher {
    int index;
    char name[100];
    int vouchers;
    char location[100];
    char profile[100];
    int price;
};

int get_index() {
    Voucher buf;
    int maxIndex = 0;
    if (!fopen_s(&fdata, "data.bin", "rb")) {
        while (fread(&buf, sizeof(Voucher), 1, fdata)) {
            if (buf.index > maxIndex) {
                maxIndex = buf.index;
            }
        }
        fclose(fdata);
        return maxIndex + 1;
    }
    return 1;
}

void input(int size) {
    Voucher buf;
    for (int i = 0; i < size; i++) {
        buf.index = get_index();
        fopen_s(&fdata, "data.bin", "ab");
        cout << "Введите название санатория: ";
        cin.ignore();
        cin.getline(buf.name, 100);
        cout << "Введите расположение: ";
        cin.getline(buf.location, 100);
        cout << "Введите лечебный профиль: ";
        cin.getline(buf.profile, 100);
        cout << "Введите цену: ";
        cin >> buf.price;
        cout << "Введите количество путевок: ";
        cin >> buf.vouchers;
        fwrite(&buf, sizeof(buf), 1, fdata);
        fclose(fdata);
    }
}

void showlist() {
    Voucher buf, vouchers[100];
    int count = 0;
    if (!fopen_s(&fdata, "data.bin", "rb")) {
        while (fread(&buf, sizeof(Voucher), 1, fdata)) {
            vouchers[count++] = buf;
        }
        fclose(fdata);
    }
    else {
        cout << "Ошибка открытия файла\n";
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(vouchers[i].profile, vouchers[j].profile) > 0 ||
                (strcmp(vouchers[i].profile, vouchers[j].profile) == 0 && strcmp(vouchers[i].name, vouchers[j].name) > 0)) {
                swap(vouchers[i], vouchers[j]);
            }
        }
    }

    cout << "Название санатория\t| Расположение\t| Лечебный профиль\t|\tЦена\t| Кол-во путевок\n";
    cout << "_________________________________________________________________________________________________\n";
    for (int i = 0; i < count; i++) 
    {
        cout << vouchers[i].name << "\r\t\t\t|" << vouchers[i].location;
        cout << "\r\t\t\t\t\t|" << vouchers[i].profile << "\r\t\t\t\t\t\t\t\t|\t"
        << vouchers[i].price << "\t|\t" << vouchers[i].vouchers << endl;
    }
}

void searchVoucher() {
    Voucher buf;
    cout << "Введите желаемый профиль: ";
    string profile;
    cin.ignore();
    getline(cin, profile);
    bool found = false;
    if (!fopen_s(&fdata, "data.bin", "rb")) {
        while (fread(&buf, sizeof(Voucher), 1, fdata)) {
            if (profile == buf.profile) {
                cout << "Найден санаторий: " << buf.name << " в " << buf.location << " по цене " << buf.price << " руб.\n";
                found = true;
            }
        }
        fclose(fdata);
    }
    if (!found) {
        cout << "Санаторий с таким профилем не найден.\n";
    }
}

void numOfVouchers(int index) {
    Voucher buf;
    fopen_s(&fnewdata, "newdata.bin", "wb");
    if (!fopen_s(&fdata, "data.bin", "rb")) {
        while (fread(&buf, sizeof(Voucher), 1, fdata)) {
            if (index == buf.index) {
                buf.vouchers--;
            }
            fwrite(&buf, sizeof(Voucher), 1, fnewdata);
        }
        fclose(fdata);
    }
    fclose(fnewdata);
    remove("data.bin");
    rename("newdata.bin", "data.bin");
}

void buyVoucher() {
    Voucher buf;
    int index, budget, userInput, summa;
    bool successfulBuy = false;
    cout << "Введите ваш бюджет: ";
    cin >> budget;
    do {
        cout << "Введите индекс желаемой путевки: ";
        cin >> index;
        if (!fopen_s(&fdata, "data.bin", "rb")) {
            while (fread(&buf, sizeof(Voucher), 1, fdata)) {
                if (index == buf.index) {
                    if (budget >= buf.price) {
                        budget -= buf.price;
                        successfulBuy = true;
                        cout << "Покупка прошла успешно!\n";
                        cout << "Название: " << buf.name << ", Профиль: " << buf.profile << ", Цена: " << buf.price << " руб.\n";
                    }
                    else {
                        cout << "Недостаточно средств!\n";
                    }
                }
            }
            fclose(fdata);
        }
        if (successfulBuy) {
            numOfVouchers(index);
        }
        cout << "Продолжить покупку? (1 - Да, 2 - Пополнить баланс, 3 - Узнать баланс, 4 - Выход): ";
        cin >> userInput;
        if (userInput == 2) {
            cout << "Введите сумму пополнения: ";
            cin >> summa;
            budget += summa;
        }
        if (userInput == 3) {
            cout << "Ваш баланс: " << budget << " руб.\n";
        }
    } while (userInput != 4);
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice, size;
    do {
        cout << "1 - Ввести данные\n2 - Вывести данные\n3 - Поиск по профилю\n4 - Купить путевку\n0 - Выход\nВыберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите количество санаториев: ";
            cin >> size;
            input(size);
            break;
        case 2:
            showlist();
            break;
        case 3:
            searchVoucher();
            break;
        case 4:
            buyVoucher();
            break;
        }
    } while (choice != 0);
}
