#include <iostream>
#include "wincomponents.h"
#include <deque>

using namespace std;

int main() {
    Component c1(5, 10, 5, 10);
    Component c2(6, 11, 2, 8);
    c1.addChildComp(&c2);

    auto mainComponent = new SignComp('.', 0, 0, 1080, 720);
    for(int i = 0; i < mainComponent->id.size(); ++i){
        cout << mainComponent->id[i] << endl;
    }

//    cout << mainComponent->id.size();
    return 0;
}