#include "MainMenu.h"
using namespace std;

void MainMenu::print_instructions()
{
	//Need screen resolution for displaying position coordinate limits
	//Hence, object creation
	GetScreenResolution get;
	cout << "2D 3 PARTICLE SIMULATOR" << endl << endl;
	cout << "This program can simulate the behavior of either 2 or 3 particles with a user entered mass, position, initial velocity,";
	cout << " and charge taking into account their mutual gravitational and electrostatic forces." << endl << endl;
	cout << "Some instructions:-\n";
	cout << "The coordinates must be within:-\nWIDTH: 20 & " << get.get_width() - 20 << endl << "HEIGHT: 20 & " << get.get_height() - 20 << endl;
	cout << "The unit of coordinates is metre by default." << endl;
	cout << "To make the effect of gravitation more apparent, the unit of mass has been set to 10^5 kg." << endl;
	cout << "To make the effect of electrostatic force more apparent, the unit of charge has been set to 10^-3 Columb (Millicoulombs)." << endl << endl;
	return;
}

//Prints options.
void MainMenu::options()
{
	cout << "Enter the corresponding number." << endl;
	cout << "1.) 2 Particle simulator." << endl;
	cout << "2.) 3 Particle simulator." << endl;
	cout << "3.) Exit." << endl;
	return;
}

//Constructor calls private printing functions
MainMenu::MainMenu()
{
	print_instructions();
	options();
	return;
}

//Prints an error message
void MainMenu::error()
{
	cout << "Please enter a valid input." << endl;
	return;
}

//Clears screen
void MainMenu::clear()
{
	system("cls");
}