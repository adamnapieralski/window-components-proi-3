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

void Shell::showMainMenu() {
    cout << "MAIN MENU\n\n";
    cout << "0 - " << "Wypisz strukture komponentow\n";
    cout << "1 - " << "Przedstaw graficznie komponenty\n";
    cout << "2 - " << "Dodaj komponent\n";
    cout << "3 - " << "Usun komponent\n";
    cout << "4 - " << "Pokaz szczegoly komponentu\n";
}

void Shell::printId(Component* component) {
    for(int i = 0; i < component->id.size(); ++i){
        cout << component->id[i];
        if(i < component->id.size() - 1)
            cout << ".";
    }
}

void Shell::showComponentsStructure(Component* component, int depth) {
    for(int i = 0; i < depth; ++i)
        cout << "\t";
    printId(component);
    cout << endl;
    ++depth;
    for(auto child : component->children)
        showComponentsStructure(child, depth);
}
void Shell::setRootComponent() {

}
