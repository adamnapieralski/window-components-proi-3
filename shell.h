//
// Created by napiad on 22.05.19.
//

#ifndef PROI_PROJECT_3_SHELL_H
#define PROI_PROJECT_3_SHELL_H

#include <iostream>
#include <sstream>
#include <deque>
#include "wincomponents.h"

class Shell{
public:
    Component* rootComponent;

    void setRootComponent();
    Component::componentTypes getComponentType();
    void showMainMenu();
    void showComponentsStructure(Component* component, int depth = 0);
    void showComponentsWindows();
    Component* selectComponent();
    void addComponent();
    void deleteComponent();
    void showComponentInfo();
    int getMenuChoice();
    bool exeMenu();


//    void printId(Component* component);

    friend void printArray(char** arr, int w, int h);
    friend std::deque<int> tokenizeID(std::string idStr);
};


#endif //PROI_PROJECT_3_SHELL_H
