//Header guards
#ifndef SIMULATE_H
#define SIMULATE_H
#include "Vector.h"
//We need screen resolution for correct calculations involving screen boundaries
#include "GetScreenResolution.h"
//We need to use file handling to store the coordinates correctly
#include <fstream>
#include <math.h>

class Simulate
{
private:
	//Mass and charge of all 3 particles, distance changes for every subsequent calculations.
	double mass[3], charge[3], distance;
	//Parameters for all 3 particles
	Vector velocity[3], position[3], accelaration[3], Force[3];
	//Constants for calculation
	const double G = 0.66743;
	const double K = 9000;
	void RunSimulation(std::ofstream& foutput);
	void ForceCalculations(int p1, int p2);
	//Checks and resolves collision of particles with the wall
	bool wallcollision(int p1);
	//Checks and resolves collision between particles
	bool particlecollision(int p1, int p2);
	//For fixing an angle in the -pi to +pi range based on the values of x and y
	void fix_angle(double x, double y, double &angle);
	//Resolves position overlap in case of particle collision
	void particle_collision_position_resolution(int p1, int p2);
public:
	//Constructor that accepts the data.
	Simulate(Vector* v, Vector* p, double* m, double* c);
};
//End header guards
#endif