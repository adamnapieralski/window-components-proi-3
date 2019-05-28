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
        default:
            throw out_of_range("Component type not handled");
    }
}

void Shell::showMainMenu() {
    cout << "\nMAIN MENU\n\n";
    cout << "1 - " << "Wypisz strukture komponentow\n";
    cout << "2 - " << "Przedstaw graficznie komponenty\n";
    cout << "3 - " << "Dodaj komponent\n";
    cout << "4 - " << "Usun komponent\n";
    cout << "5 - " << "Pokaz szczegoly komponentu\n";
    cout << "0 - " << "Wyjscie\n";
}

void Shell::showComponentsStructure(Component* component, int depth) {

    for(int i = 0; i < depth; ++i)
        cout << "\t";
    cout << component->id << endl;
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

    //free memory
    for(int i = 0; i < this->rootComponent->h; ++i){
        delete[] displayArray[i];
    }
    delete[] displayArray;
}

deque<int> tokenizeID(string idStr) {
    size_t start;
    size_t end = 0;
    const char sep = '.';
    deque<int> id;
    while((start = idStr.find_first_not_of(sep, end)) != string::npos){
        end = idStr.find(sep, start);
        string idTempStr = idStr.substr(start, end - start);
        try {
            int idTempInt = stoi(idTempStr);
            id.push_back(idTempInt);

        }
        catch(invalid_argument&){
            id.clear();
            return id;
        }
    }
    return id;
}

Component* Shell::selectComponent() {
    cout << "Podaj ID wybranego komponentu:\n";
    string idStr;
    cin.clear();
    cin.ignore(INT8_MAX, '\n');
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
        return nullptr;
    }
    else{
        return foundComp;
    }
}

void Shell::addComponent() {
    cout << "Zdefiniuj komponent, ktorego potomkiem ma sie stac dodawany komponent.\n";
    Component* parent = this->selectComponent();
    if(!parent)
        return;
    //wybor typu komponentu
    auto newType = this->getComponentType();
    auto newComp = newComponent(newType);

    cout << "Podaj znak/tekst charakterystyczny dla dodawanego komponentu\n";
    string character;
    cin.clear();
    cin.ignore(INT8_MAX, '\n');

    getline(cin, character);
    while(character.empty() || (newType == Component::sign && character.size() > 1)){
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
    while ((cout << "\tszerokosc: " && !(cin >> w)) || w < 0 || w > parent->w - x || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    while ((cout << "\twysokosc: " && !(cin >> h)) || h < 0 || h > parent->h - y || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    newComp->setPosition(x, y);
    newComp->setDimensions(w, h);

    parent->addChildComp(newComp);
}

void Shell::deleteComponent() {
    cout << "Zdefiniuj komponent, który chcesz usunac.\n";
    Component* delComp = this->selectComponent();
    if(delComp == this->rootComponent){
        cout << "Nie mozna usunac komponentu nadrzednego.\n";
    }
    else{
        delete delComp;
        cout << "Usunieto komponent.\n";
    }
}

void Shell::showComponentInfo(){
    cout << "Zdefiniuj komponent, o ktorym chcesz uzyskac szczegolowe informacje\n";
    Component* infoComponent = this->selectComponent();
    if(infoComponent)
        infoComponent->showInfo();
}

int Shell::getMenuChoice(){
    int choice;
    while (!(std::cin >> choice) || std::cin.peek() != '\n')
    {
        std::cout << "Niepoprawne dane. Wprowadz ponownie." << std::endl;
        std::cin.clear();
        std::cin.ignore(INT8_MAX, '\n');
    }
    return choice;
}

bool Shell::exeMenu() {
    this->showMainMenu();
    switch(this->getMenuChoice()){
        case 0:{
            if(this->rootComponent) delete this->rootComponent;
            std::cout << "\nWYJSCIE\n";
            return false;
        }
        case 1:
            cout << endl << "Struktura komponentów" << endl;
            this->showComponentsStructure(this->rootComponent);
            cout << endl;
            return true;
        case 2:
            this->showComponentsWindows();
            return true;
        case 3:
            this->addComponent();
            return true;
        case 4:
            this->deleteComponent();
            return true;
        case 5:
            this->showComponentInfo();
            return true;
        default:
            std::cout << "Niepoprawne polecenie. Sprobuj ponownie.\n\n";
            return true;
    }
}

void Shell::setRootComponent() {
    cout << "Zdefiniuj glowny - nadrzedny komponent.\n\n";
    //wybor typu komponentu
    auto newType = this->getComponentType();
    auto rootComp = newComponent(newType);


    cout << "Podaj znak/tekst charakterystyczny dla dodawanego komponentu\n";
    string character;
    cin.clear();
    cin.ignore(INT8_MAX, '\n');
    getline(cin, character);

    while(character.size() == 0 || (newType == Component::sign && character.size() > 1)){
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        getline(cin, character);
    }
    rootComp->setCharacteristic(character);


    cout << "Podaj jego wymiary:\n";
    int w, h;
    while ((cout << "\tszerokosc: " && !(cin >> w)) || w < 0 || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    while ((cout << "\twysokosc: " && !(cin >> h)) || h < 0 || cin.peek() != '\n')
    {
        cout << "Niepoprawne dane. Wprowadz ponownie." << endl;
        cin.clear();
        cin.ignore(INT8_MAX, '\n');
    }
    rootComp->setPosition(0, 0);
    rootComp->setDimensions(w, h);
    rootComp->parent = nullptr;
    this->rootComponent = rootComp;
}




