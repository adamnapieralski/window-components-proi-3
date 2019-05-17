//
// Created by napiad on 17.05.19.
//

#ifndef PROI_PROJECT_3_WINCOMPONENTS_H
#define PROI_PROJECT_3_WINCOMPONENTS_H

#include <iostream>
#include <vector>

enum componentTypes {
        title,
        sign
};

class Component{
public:
    unsigned int x, y;  //position of window's rectangle upper left corner in global coord sys
    unsigned int w, h;  //dimensions: width and height

    std::vector <Component> children;   //components contained in this component

    Component();
    Component(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void addChildComp(Component child);

    friend Component* newComponent(int componentType);

};

class TitleComp: public Component{
public:
    std::string title;
};

class SignComp: public Component{
public:
    char sign;
};

#endif //PROI_PROJECT_3_WINCOMPONENTS_H
