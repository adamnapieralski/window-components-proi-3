//
// Created by napiad on 22.05.19.
//

#include "shell.h"

using namespace std;

Component::componentTypes Shell::getComponentType() {
    cout << "Wybierz typ komponentu:" << endl;
    cout << "\t" << Component::title << " - zawierajacy dany napis" << endl;
    cout << "\t" << Component::sign << " - zawierajacy dany znak" << endl;
    int choice;
    while ((!(cin >> choice)) || choice < Component::title || choice > Component::sign || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    switch(choice){
        case 0: return Component::title;
        case 1: return Component::sign;
    }
}
void Shell::setRootComponent() {

}
