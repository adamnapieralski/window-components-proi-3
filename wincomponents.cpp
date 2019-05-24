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

Component::~Component() {
    if(this->parent){
        auto childErase = find(this->parent->children.begin(), this->parent->children.end(), this);
        this->parent->children.erase(childErase);
    }

    for(auto child : this->children){
        delete child;
    }
}

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

    if(maxId + 1 == lastIds.size())
        return maxId + 1;

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
        child->parent = this;
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

//    for(int i = 0; i < this->h; ++i){
//        delete[] ptsDisplayArray[i];
//    }
//    delete[] ptsDisplayArray;

    return displayArray;
}

Component* Component::findComponent(std::deque<int> id) {
    if(id == this->id)
        return this;

    std::deque<int> partId(id.begin(), id.begin() + this->id.size());
    if(partId !=  this->id){
        return nullptr;
    }
    std::deque<int> partChildId(id.begin(), id.begin() + this->id.size() + 1);
    for(auto child : this->children){
        Component* foundComp = child->findComponent(id);
        if(foundComp){
            return foundComp;
        }
    }
    return nullptr;
}

int Component::getGlobalX() {
    int x = 0;
    if(this->parent){
        x += this->parent->getGlobalX();
    }
    x += this->x;
    return x;
}

int Component::getGlobalY() {
    int y = 0;
    if(this->parent){
        y += this->parent->getGlobalX();
    }
    y += this->y;
    return y;
}

TitleComp::TitleComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->title = "";
    this->id.push_back(0);
}

TitleComp::TitleComp(std::string title, int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->title = title;
    this->id.push_back(0);
    this->parent = nullptr;
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

void TitleComp::setCharacteristic(std::string characteristic) {
    this->title = characteristic;
}

void TitleComp::showInfo() {
    std::cout << "\tID:\t" << this->id << std::endl;
    std::cout << "\tWypelnienie:\t" << this->title << std::endl;
    std::cout << "\tWymiary (szer x wys):\t" << this->w << " x " << this->h << std::endl;
    std::cout << "\tPolozenie wzgledem 'rodzica' (x, y):\t" << "(" << this->x << ", " << this->y << ")" << std::endl;
    std::cout << "\tPolozenie globalne (x, y):\t" << "(" << this->getGlobalX() << ", " << this->getGlobalY()
    << ")" << std::endl;
    std::cout << "\t'Rodzic':\t" << this->parent->id << std::endl;
    std::cout << "\tPotomkowie:\t" << std::endl;
    for(auto child : this->children){
        std::cout << "\t\t" << child->id << std::endl;
    }
    std::cout << std::endl;
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

void SignComp::setCharacteristic(std::string characteristic) {
    this->sign= characteristic[0];
}


SignComp::SignComp() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->sign = '\0';
    this->id.push_back(0);
}

SignComp::SignComp(char &sign, int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->sign = sign;
    this->id.push_back(0);
    this->parent = nullptr;
}

void SignComp::showInfo() {
    std::cout << "\tID:\t" << this->id << std::endl;
    std::cout << "\tWypelnienie:\t" << this->sign << std::endl;
    std::cout << "\tWymiary (szer x wys):\t" << this->w << " x " << this->h << std::endl;
    std::cout << "\tPolozenie wzgledem 'rodzica' (x, y):\t" << "(" << this->x << ", " << this->y << ")" << std::endl;
    std::cout << "\tPolozenie globalne (x, y):\t" << "(" << this->getGlobalX() << ", " << this->getGlobalY()
              << ")" << std::endl;
    std::cout << "\t'Rodzic':\t" << this->parent->id << std::endl;
    std::cout << "\tPotomkowie:\t" << std::endl;
    for(auto child : this->children){
        std::cout << "\t\t" << child->id << std::endl;
    }
    std::cout << std::endl;
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

std::ostream &operator<<(std::ostream &os, const std::deque<int> &id) {
    for(auto i = id.begin(); i != id.end(); i++){
        os << *i;
        if(i != id.end() - 1)
            os << ".";
    }
    return os;
}

