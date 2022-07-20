#include <iostream>
#include "GetScreenResolution.h"
#include "MainMenu.h"
#include "Vector.h"
#include "Simulate.h"
#include "SimulateGraphics.h"

using namespace std;

void LoadParticle(double& m, double& c, Vector& v, Vector& p, MainMenu& obj);

int main(int argc, char* args[])
{
	MainMenu menu;
	double* mass = new double[3];
	double* charge = new double[3];
	Vector* velocity = new Vector[3];
	Vector* position = new Vector[3];

	int choice;
	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1:
			for (int i = 0; i < 2; i++)
			{
				menu.clear();
				cout << "Particle " << i + 1 << endl;
				LoadParticle(mass[i], charge[i], velocity[i], position[i], menu);
			}
			mass[2] = 0;
			charge[2] = 0;
			velocity[2] = Vector(0, 0);
			position[2] = Vector(-800, -800);
			break;
		case 2:
			for (int i = 0; i < 3; i++)
			{
				menu.clear();
				cout << "Particle " << i + 1 << endl;
				LoadParticle(mass[i], charge[i], velocity[i], position[i], menu);
			}
			break;
		case 3:
			return 0;
			break;
		default:
			menu.clear();
			menu = MainMenu();
			menu.error();
			choice = 0;
		}
	} while (choice == 0);
	Simulate sim(&velocity[0], &position[0], &mass[0], &charge[0]);
	SimulateGraphics x;
	x.LoadTheCircles();
	delete[] mass;
	delete[] charge;
	delete[] position;
	delete[] velocity;
	return 0;
}

void LoadParticle(double& m, double& c, Vector& v, Vector& p, MainMenu& obj)
{
	double mTemp, cTemp, xTemp, yTemp;
	do
	{
		cout << "Enter the mass of the particle." << endl;
		cin >> mTemp;
		try
		{
			if (mTemp <= 0)
			{
				throw 404;
			}
		}
		catch (int x)
		{
			obj.error();
		}
	} while (mTemp <= 0);
	m = mTemp;
	cout << "Enter the charge of the particle." << endl;
	cin >> cTemp;
	c = cTemp;
	bool flag = true;
	do
	{
		flag = true;
		GetScreenResolution get;
		cout << "Enter the position of the particle." << endl;
		cout << "X: ";
		cin >> xTemp;
		try
		{
			if (xTemp<20 || xTemp>get.get_width() - 20)
			{
				throw 404;
			}
		}
		catch (int x)
		{
			obj.error();
			flag = false;
			continue;
		}
		cout << "Y: ";
		cin >> yTemp;
		try
		{
			if (yTemp<20 || yTemp>get.get_height() - 20)
			{
				throw 404;
			}
		}
		catch (int x)
		{
			obj.error();
			flag = false;
			continue;
		}
		p.set(xTemp, yTemp);
	} while (flag == false);
	cout << "Enter the velocity of the particle in the format A B, where A is the i component of the velocity vector and B is the j component." << endl;
	cin >> v;
	return;
}