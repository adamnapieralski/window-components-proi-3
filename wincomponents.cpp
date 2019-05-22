//
// Created by napiad on 17.05.19.
//

#include "wincomponents.h"


//Component::Component() {
//    this->x = 0;
//    this->y = 0;
//    this->w = 0;
//    this->h = 0;
//    this->id.push_back(0);
//}
//
//Component::Component(int x, int y, int w, int h) {
//    this->x = x;
//    this->y = y;
//    this->w = w;
//    this->h = h;
//    this->id.push_back(0);
//
//}

void Component::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Component::setDimensions(int w, int h) {
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


bool Component::isContained(Component *child) {
    if((child->x >= 0) && (child->x + child->w <= this->w) && (child->y >= 0) && (child->y + child->h <= this->h))
        return true;
    else
        return false;
}

void Component::addChildComp(Component* child) {

    if(this->isContained(child)){
        //set smallest id to set to child
        child->id = this->id;
        child->id.push_back(this->newChildId());
        this->children.push_back(child);
    }
    else{
        std::cout << "temp error" << std::endl;
    }

}

char** Component::getDisplayArray() {
    char** displayArray = new char*[this->h];
    char*** ptsDisplayArray = new char**[this->h];

    for(int i = 0; i < this->h; ++i){
        displayArray[i] = new char[this->w];
        ptsDisplayArray[i] = new char*[this->w];
        for(int j = 0; j < this->w; ++j){
            displayArray[i][j] = ' ';
            ptsDisplayArray[i][j] = &displayArray[i][j];
        }
    }

    this->fillDisplayArray(ptsDisplayArray);

    return displayArray;
}

TitleComp::TitleComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->title = "";
}

TitleComp::TitleComp(std::string title, int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->title = title;
}

void TitleComp::fillDisplayArray(char*** dispArr) {
    //fill array with current component's title
    for(int i = 0; i < this->h; ++i){
        int titleIter = 0;
        for(int j = 0; j < this->w; ++j){
            if(titleIter >= this->title.size()) titleIter = 0;
            *dispArr[i][j] = this->title[titleIter];
            ++titleIter;
        }
    }
    //iterate through children
    for(auto child : this->children){
        //create array of pointers for child to fill (child's size, with pointers to original one)
        char*** childDispArray = new char**[child->h];
        for(int i = 0; i < child->h; ++i){
            childDispArray[i] = new char*[child->w];
            for(int j = 0; j < child->w; ++j){
                childDispArray[i][j] = dispArr[child->y + i][child->x + j];
            }
        }
        //recursive filling
        child->fillDisplayArray(childDispArray);
    }
    //free memory
    for(int i = 0; i < this->h; ++i){
        delete[] dispArr[i];
    }
    delete[] dispArr;
}


void SignComp::fillDisplayArray(char*** dispArr) {
    //fill array with current component's title
    for(int i = 0; i < this->h; ++i){
        int titleIter = 0;
        for(int j = 0; j < this->w; ++j){
            *dispArr[i][j] = this->sign;
            ++titleIter;
        }
    }
    //iterate through children
    for(auto child : this->children){
        //create array of pointers for child to fill (child's size, with pointers to original one)
        char*** childDispArray = new char**[child->h];
        for(int i = 0; i < child->h; ++i){
            childDispArray[i] = new char*[child->w];
            for(int j = 0; j < child->w; ++j){
                childDispArray[i][j] = dispArr[child->y + i][child->x + j];
            }
        }
        //recursive filling
        child->fillDisplayArray(childDispArray);
    }
    //free memory
    for(int i = 0; i < this->h; ++i){
        delete[] dispArr[i];
    }
    delete[] dispArr;
}


SignComp::SignComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->sign = '\0';
}

SignComp::SignComp(char &sign, int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->sign = sign;

}

Component* newComponent(int componentType) {
    switch(componentType){
        case 0:
            return new TitleComp();
        case 1:
            return new SignComp();
    }
}

void deleteComponent(Component* comp){
    if(!comp->children.empty()){
        //for(auto child = comp->children.begin(); child != comp->children.end(); child++){
        for(auto &child : comp->children){
            deleteComponent(child);
        }
    }
    else{
        //find iterator to the comp pointer in parent's children vector
        auto eraseComp = std::find(comp->parent->children.begin(), comp->parent->children.end(), comp);
        //erase it from parent's children vector
        comp->parent->children.erase(eraseComp);
        //finally delete
        delete comp;
    }
}
