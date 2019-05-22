#include <iostream>
#include "wincomponents.h"
#include <deque>

using namespace std;

int main() {
    auto t1 = new TitleComp("xyz", 0, 0, 12, 6);
    auto t2 = new TitleComp(".", 2, 2, 6, 3);
    auto t3 = new TitleComp("|", 1, 1, 4, 1);
    auto t4 = new TitleComp("-", 6, 0, 5, 4);
    t2->addChildComp(t3);
    t1->addChildComp(t2);
    t1->addChildComp(t4);


    char** tablica = t1->getDisplayArray();
    for(int i = 0; i < t1->h; ++i){
        for(int j = 0; j < t1->w; ++j){
            cout << tablica[i][j];
        }
        delete[] tablica[i];
        cout << endl;
    }
    delete[] tablica;
    delete t1;
    delete t2;
    delete t3;
    delete t4;

    return 0;
}