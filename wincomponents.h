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
    std::deque <int> id; //id of a component
    int x, y;  //position of window's rectangle upper left corner in global coord sys
    int w, h;  //dimensions: width and height

    std::vector <Component*> children;   //pointers to components contained in this component
    Component* parent;  //pointer to parent of this component

    Component();
    Component(int x, int y, int w, int h);

    void addChildComp(Component* child);
    int newChildId();

    void setPosition(int x, int y);
    void setDimensions(int w, int h);

    virtual char** getDisplayArray() = 0;

    friend Component* newComponent(int componentType);
    friend void deleteComponent(Component* comp);
    friend bool isContained(Component* parent, Component* child);

};

class TitleComp: public Component{
public:
    std::string title;

    TitleComp();
    TitleComp(std::string &title, int x, int y, int w, int h);

    char** getDisplayArray() override;

};

class SignComp: public Component{
public:
    char sign;
    SignComp();
    SignComp(char sign, int x, int y, int w, int h);

    char** getDisplayArray() override;
};

#endif //PROI_PROJECT_3_WINCOMPONENTS_H
