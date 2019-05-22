//
// Created by napiad on 22.05.19.
//

#ifndef PROI_PROJECT_3_SHELL_H
#define PROI_PROJECT_3_SHELL_H

#include "wincomponents.h"

class Shell{
public:
    Component* rootComponent;

    void setRootComponent();
    Component::componentTypes getComponentType();
    void showMainMenu();
    void showComponentsStructure();

};

#endif //PROI_PROJECT_3_SHELL_H
