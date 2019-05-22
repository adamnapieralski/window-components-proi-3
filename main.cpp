#include <iostream>
#include "wincomponents.h"
#include <deque>

using namespace std;


void cos(int*** array){
    *array[0][0] = 1;
    *array[0][1] = 2;
    *array[1][0] = 3;
    *array[1][1] = 4;
}
int main() {
    //auto mainComponent = new SignComp('.', 0, 0, 1080, 720);

    int** vals = new int*[8];
    for(int i = 0; i < 8; i++){
        vals[i] = new int[6];
    }

    int*** a = new int**[8];
    for(int i = 0; i < 8; i++){
        a[i] = new int*[6];
        for(int j = 0; j < 6; j++){
            a[i][j] = &vals[i][j];
            cout << *a[i][j] << " ";
        }
        cout << endl;
    }
    //int* ptr = &a[2][2];
//    int *ptr1 = &a[2][2];
//    int** ptr = &ptr1;

    cout << endl << endl;
    const int x = 8, y = 8;

    //vector<vector<int*>>

    int*** b = new int**[2];
    for(int i = 0; i < 2; i++){
        b[i] = new int*[2];
        for(int j = 0; j < 2; j++){
            b[i][j] = a[2 + i][2 + j];
        }
    }
    cos(b);


    cout << endl << endl;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 6; j++){
            cout << vals[i][j] << " ";
        }
        cout << endl;
    }

    int cint = 5;
    int** c = new int*[8];
    for(int i = 0; i < 8; i++){
        c[i] = &cint;
        cout << *c[i] << " ";
    }

    string tekst = "siema";
    char tekst_char = tekst[0];
    cout << tekst_char;

    cout << endl;
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
        cout << endl;
    }
    return 0;
}