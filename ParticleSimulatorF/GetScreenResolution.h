//Header guards
#ifndef GETSCREENRESOLUTION_H
#define GETSCREENRESOLUTION_H
#include <wtypes.h>
#include <iostream>

class GetScreenResolution
{
private:
	//Private integers to store screen resolution
	int width, height;
public:
	//Constructor that calculates the screen resolution and assigns to private variables
	GetScreenResolution();
	//Function used to obtain width
	int get_width();
	//Function used to obtain height
	int get_height();
};
//End header guards
#endif