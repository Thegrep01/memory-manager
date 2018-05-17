#include <iostream>
#include <ctime>
#define SIZE 256
using namespace std;

int all = 0; //êîëè÷åñòâî ïðîöåññîâ íà äàííûé ìîìåíò
int matr[1000]; //àäðåñà ïðîöåññîâ
int buff[SIZE]; // ïàìÿòü

void Input() {
    int length = rand() % 9 + 1;
    int allocateMemory = SIZE;
    while (allocateMemory / 2 >= length)
        allocateMemory /= 2;
    int k = 0;
    all++;
    bool flag1 = false;
    for (k = 0; k < SIZE; k += allocateMemory) {
        bool flag = true;
        for (int i = 0; i < allocateMemory; i++) {
            if (buff[k + i] != 0) {
                flag = false;
                break;
            }
        }
        if (flag == true) {
            flag1 = true;
            break;
        }
    }
    if (flag1 == true) {
        for (int i = 0; i < length; i++) {
            buff[k + i] = all;
        }
        matr[all] = k;
    }
}
void Output() {
    int i;
    int p = 0;

    do {
        i = rand() % all;
        p++;
    }
    while (p < 10 && matr[i] == -1);
    if (p != 10) {
        int k = matr[i];
        int elem = buff[k];
        while (buff[k] == elem) {
            buff[k] = 0;
            k++;
        }
        matr[i] = -1;
    }
}
void Defrag() {
    int i = 0;
    bool flag = true;
    while (i < SIZE) {
        while (buff[i] != 0)
            i++;
        if (i >= SIZE)
            break;
        int k = i;
        while (buff[k] == 0) {
            k++;
            if ( k >= SIZE) {
                flag = false;
                break;
            }
        }
        if (!flag)
            break;
        int m = k;
        while (m < SIZE && buff[m] == buff[k])
            m++;
        int length = m - k;
        matr[buff[k]] = i;
        for (int m = 0; m < length; m++) {
            buff[i + m] = buff[k + m];
            buff[k + m] = 0;
        }
        i += length;
    }
}
void Print() {
    for (int i = 0; i < SIZE; i++) {
        cout << buff[i] << " ";
    }
    cout << endl;
}
int main() {
    srand(time(NULL));
    int t;
    while (true) {
        t = rand();
        system("clear");
        cout << "Create" << endl;
        Input();
        Print();

        if (t % 3 == 0) {
            system("clear");
            cout << "Delete" << endl;
            Output();
            Print();
            cout << "Defragment" << endl;
            Defrag();
            Print();
        }
        getchar();
    }


}