//
// Created by napiad on 17.05.19.
//

#ifndef PROI_PROJECT_3_WINCOMPONENTS_H
#define PROI_PROJECT_3_WINCOMPONENTS_H

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>

enum componentTypes {
        title,
        sign
};

class Component{
public:
    std::deque <unsigned int> id; //id of a component
    unsigned int x, y;  //position of window's rectangle upper left corner in global coord sys
    unsigned int w, h;  //dimensions: width and height

    std::vector <Component*> children;   //components contained in this component

    Component();
    Component(unsigned int x, unsigned int y, unsigned int w, unsigned int h);

    void addChildComp(Component* child);
    int newChildId();

    friend Component* newComponent(int componentType);

};

class TitleComp: public Component{
public:
    std::string title;

    TitleComp();
};

class SignComp: public Component{
public:
    char sign;
    SignComp();
};

#endif //PROI_PROJECT_3_WINCOMPONENTS_H
