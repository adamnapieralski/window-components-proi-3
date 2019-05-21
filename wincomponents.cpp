//
// Created by napiad on 17.05.19.
//

#include "wincomponents.h"


Component::Component() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->id.push_back(0);
}

Component::Component(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

int Component::newChildId() {
    //find smallest id to set to the child
    std::deque <int> lastIds;
    int maxId = 0;
    for(int i = 0; i < this->children.size(); ++i){
        lastIds.push_back(this->children[i]->id.back());
        if(this->children[i]->id.back() > maxId){
            maxId = this->children[i]->id.back();
        }
    }

    std::sort(lastIds.begin(), lastIds.end());

    for(int i = 0; i < maxId; ++i){
        if(i >= lastIds.size()){
            return maxId + 1;
        }
        if(i != lastIds[i]){
            return i;
        }
    }
}

void Component::addChildComp(Component* child) {
    //set smallest id to set to child
    child->id = this->id;
    child->id.push_back(this->newChildId());
    this->children.push_back(child);
}

TitleComp::TitleComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->id.push_back(0);
    this->title = "";
}

TitleComp::TitleComp(std::string &title, int x, int y, int w, int h) {
    this->title = title;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

SignComp::SignComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->id.push_back(0);
    this->sign = '\0';
}

SignComp::SignComp(char sign, int x, int y, int w, int h) {
    this->sign = sign;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

//Component* newComponent(int componentType) {
//    switch(componentType){
//        case 0:
//            return new TitleComp();
//        case 1:
//            return new SignComp();
//    }
//}
