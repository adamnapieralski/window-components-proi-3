//
// Created by napiad on 22.05.19.
//

#ifndef PROI_PROJECT_3_SHELL_H
#define PROI_PROJECT_3_SHELL_H

#include "wincomponents.h"
#include <deque>

class Shell{
public:
    Component* rootComponent;

    void setRootComponent();
    Component::componentTypes getComponentType();
    void showMainMenu();
    void showComponentsStructure(Component* component, int depth = 0);
    void showComponentsWindows();


    void printId(Component* component);

    friend void printArray(char** arr, int w, int h);

};

#endif //PROI_PROJECT_3_SHELL_H
