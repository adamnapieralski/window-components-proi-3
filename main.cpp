#include <iostream>
#include "wincomponents.h"

int main() {
    Component c1(5, 10, 5, 10);
    Component c2(6, 11, 2, 8);
    c1.addChildComp(&c2);

    auto mainComponent = new Component(0, 0, 1080, 720);


    return 0;
}