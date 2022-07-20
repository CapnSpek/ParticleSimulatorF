//Header guards
#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
//We need screen resolution to be able to correctly display position coordinate limits
#include "GetScreenResolution.h"
//Required for clearing the screen
#include <Windows.h>
class MainMenu
{
private:
	//Both functions are used for printing only
	void print_instructions();
	void options();
public:
	//Constructor that calls the private printing functions
	MainMenu();
	//To display an error in input
	void error();
	//Clearing screen
	void clear();
};
//End header guards
#endif