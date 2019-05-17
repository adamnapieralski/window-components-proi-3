//
// Created by napiad on 17.05.19.
//

#include "wincomponents.h"


Component::Component() {
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
}

Component::Component(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Component::addChildComp(Component child) {
    this->children.push_back(child);
}
