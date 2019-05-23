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

class Component{
public:
    std::deque <int> id; //id of a component
    int x, y;  //position of window's rectangle upper left corner in global coord sys
    int w, h;  //dimensions: width and height

    enum componentTypes {
        title,
        sign
    };

    std::vector <Component*> children;   //pointers to components contained in this component
    Component* parent;  //pointer to parent of this component

//    Component();
//    Component(int x, int y, int w, int h);

    void addChildComp(Component* child);
    int newChildId();

    void setPosition(int x, int y);
    void setDimensions(int w, int h);

    bool isContained(Component* child);
    char** getDisplayArray();
    virtual void fillDisplayArray(char*** dispArr) = 0;

    Component* findComponent(std::deque<int> id);

    friend Component* newComponent(int componentType);
    friend void deleteComponent(Component* comp);
};

class TitleComp: public Component{
public:
    std::string title;

    TitleComp();
    TitleComp(std::string title, int x, int y, int w, int h);

    //char** getDisplayArray() override;
    void fillDisplayArray(char*** dispArr) override;

};

class SignComp: public Component{
public:
    char sign;
    SignComp();
    SignComp(char &sign, int x, int y, int w, int h);

    //char** getDisplayArray() override;
    void fillDisplayArray(char*** dispArr) override;

};

#endif //PROI_PROJECT_3_WINCOMPONENTS_H
