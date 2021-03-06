/*
 * Name: wincomponents.h
 * Purpose: Custom library headers file for window components classes
 * @author Adam Napieralski
 * @version 0.1 28/05/2019
 */


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

    Component();
    Component(int x, int y, int w, int h);

    ~Component();

    void addChildComp(Component* child);
    int newChildId();

    void setPosition(int x, int y);
    void setDimensions(int w, int h);

    bool isContained(Component* child);
    char** getDisplayArray();
    int getGlobalX();
    int getGlobalY();
    virtual void fillDisplayArray(char*** dispArr) = 0;
    virtual void setCharacteristic(std::string characteristic) = 0;
    virtual void showInfo() = 0;

    Component* findComponent(std::deque<int> id);

    friend void deleteComponent(Component* comp);

};

class TitleComp: public Component{
public:
    std::string title;

    TitleComp();
    TitleComp(std::string title, int x, int y, int w, int h);

    void fillDisplayArray(char*** dispArr) override;
    void setCharacteristic(std::string characteristic) override;
    void showInfo() override;


};

class SignComp: public Component{
public:
    char sign;
    SignComp();
    SignComp(char &sign, int x, int y, int w, int h);

    void fillDisplayArray(char*** dispArr) override;
    void setCharacteristic(std::string characteristic) override;
    void showInfo() override;

};

Component* newComponent(int componentType);

std::ostream& operator<<(std::ostream& os, const std::deque<int>& id);

#endif //PROI_PROJECT_3_WINCOMPONENTS_H
