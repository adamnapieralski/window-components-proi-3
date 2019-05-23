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

void printArray(char** arr, int w, int h){
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            cout << arr[i][j];
        }
        cout << endl;
    }
}

void Shell::showComponentsWindows() {
    char** displayArray = this->rootComponent->getDisplayArray();
    printArray(displayArray, this->rootComponent->w, this->rootComponent->h);
}

deque<int> tokenizeID(string idStr) {
    size_t start;
    size_t end = 0;
    const char sep = '.';
    deque<int> id;
    while((start = idStr.find_first_not_of(sep, end)) != string::npos){
        end = idStr.find(sep, start);
        string idTempStr = idStr.substr(start, end - start);
        int idTempInt;
        istringstream iss (idTempStr);
        iss >> idTempInt;
        if(iss.good()){
            id.clear();
            return id;
        }
        id.push_back(idTempInt);
    }
    return id;
}

Component* Shell::selectComponent() {
    cout << "Podaj ID wybranego komponentu:\n";
    string idStr;
    getline(cin, idStr);
    std::deque<int> id = tokenizeID(idStr);
    while(id.empty()){
        cout << "Niepoprawne dane. Wprowadz ID ponownie.\n";
        getline(cin, idStr);
        id = tokenizeID(idStr);
    }
    Component* foundComp = this->rootComponent->findComponent(id);
    if(!foundComp){
        cout << "Nie znaleziono komponentu o podanym ID.\n";
    }
    else{
        return foundComp;
    }
}

void Shell::addComponent() {
    cout << "Zdefiniuj komponent, ktorego potomkiem ma sie stac dodawany komponent.\n";
    Component* parent = this->selectComponent();
    //wybor typu komponentu
    auto newType = this->getComponentType();
    auto newComp = newComponent(newType);

    cout << "Podaj znak/tekst charakterystyczny dla komponentu\n";
    string character = "";
    cin.clear();
    cin.ignore(INT8_MAX, '\n');
    getline(cin, character);
    while(character.size() == 0 || (newType == Component::sign && character.size() > 1)){
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        getline(cin, character);
    }
    newComp->setCharacteristic(character);

    cout << "Podaj polozenie nowego komponentu wzgledem 'rodzica'\n";
    int x, y;
    while ((cout << "\tx: " && !(cin >> x)) || x < 0 || x >= parent->w || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    while ((cout << "\ty: " && !(cin >> y)) || y < 0 || y >= parent->h || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    cout << "Podaj wymiary nowego komponentu\n";
    int w, h;
    while ((cout << "\tszerokosc: " && !(cin >> w)) || w < 0 || w >= parent->w - x || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    while ((cout << "\twysokosc: " && !(cin >> h)) || h < 0 || h >= parent->h - y || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    newComp->setPosition(x, y);
    newComp->setDimensions(w, h);

    parent->addChildComp(newComp);
}
void Shell::setRootComponent() {

}




