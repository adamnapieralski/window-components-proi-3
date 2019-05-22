#include <iostream>
#include <deque>

#include "wincomponents.h"
#include "shell.h"

using namespace std;

enum componentTypes2 {
    title,
    sign
};


int main() {
    auto t1 = new TitleComp("xyz", 0, 0, 12, 6);
    cout << t1->id.size() << endl;
    auto t2 = new TitleComp(".", 2, 2, 6, 3);
    auto t3 = new TitleComp("|", 1, 1, 4, 1);
    auto t4 = new TitleComp("-", 6, 0, 5, 4);
    t1->addChildComp(t2);
    t1->addChildComp(t4);
    t2->addChildComp(t3);


    char** tablica = t1->getDisplayArray();
    for(int i = 0; i < t1->h; ++i){
        for(int j = 0; j < t1->w; ++j){
            cout << tablica[i][j];
        }
        delete[] tablica[i];
        cout << endl;
    }
    delete[] tablica;

    Shell shell;
    shell.rootComponent = t1;
    shell.showComponentsStructure(t1);
    shell.showComponentsWindows();
    delete t1;
    delete t2;
    delete t3;
    delete t4;

    return 0;
}