#include <iostream>
#include <deque>

#include "shell.h"
#include "wincomponents.h"


using namespace std;

int main() {

    vector<int> vec{1};
    auto found = find(vec.begin(), vec.end(), 1);
    cout << vec.size();
    vec.erase(found);
    cout << endl << vec.size();

    Shell shell;
    shell.setRootComponent();
    while(shell.exeMenu()){}

//    auto t1 = new TitleComp("xyz", 0, 0, 12, 6);
//    cout << t1->id.size() << endl;
//    auto t2 = new TitleComp(".", 2, 2, 6, 3);
//    auto t3 = new TitleComp("|", 1, 1, 4, 1);
//    auto t4 = new TitleComp("-", 6, 0, 5, 4);
//    t1->addChildComp(t2);
//    t1->addChildComp(t4);
//    t2->addChildComp(t3);
//
//
//    char** tablica = t1->getDisplayArray();
//    for(int i = 0; i < t1->h; ++i){
//        for(int j = 0; j < t1->w; ++j){
//            cout << tablica[i][j];
//        }
//        delete[] tablica[i];
//        cout << endl;
//    }
//    delete[] tablica;
//
//    t4->showInfo();
//    Shell shell;
//    shell.rootComponent = t1;
//    shell.showMainMenu();
//    shell.showComponentsStructure(t1);
//    shell.showComponentsWindows();
//    shell.addComponent();
//    shell.showComponentsStructure(t1);
//    shell.showComponentsWindows();
//    shell.showComponentInfo();
//    delete t1;
//    delete t2;
//    delete t3;
//    delete t4;

    return 0;
}