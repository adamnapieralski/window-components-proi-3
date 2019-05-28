/*
 * Name: proi3.cpp
 * Purpose: Program for PROI classes - creating window-component structure
 * @author Adam Napieralski
 * @version 0.1 28/05/2019
 */

#include "shell.h"
#include "wincomponents.h"


using namespace std;

int main() {
    Shell shell;
    shell.setRootComponent();
    while(shell.exeMenu()){}

    return 0;
}