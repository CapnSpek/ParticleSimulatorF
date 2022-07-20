#include "Simulate.h"
# define M_PI           3.14159265358979323846
using namespace std;

//Constructor accepts and assigns the data, and opens a file stream
Simulate::Simulate(Vector* v, Vector* p, double* m, double* c)
{
	for (int i = 0; i < 3; i++)
	{
		mass[i] = m[i];
		position[i] = p[i];
		velocity[i] = v[i];
		charge[i] = c[i];
	}
	ofstream foutput;
	foutput.open("Coordinates.txt");
	RunSimulation(foutput);
	foutput.close();
}

//Takes file stream as parameter
void Simulate::RunSimulation(ofstream& foutput)
{
	for (int i = 0; i < 1500; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//Writes the current position, sets net force and accelaration to 0.
			foutput << position[j] << " ";
			Force[j].set(0, 0);
			accelaration[j].set(0, 0);
		}
		foutput << endl;
		//Checks for wall collision of all 3 particles and the function resolves if any
		for (int j = 0; j < 3; j++)
		{
			wallcollision(j);
		}
		//Checks for particle collision among all the particles and the function resolves if any
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + 1; j < 3; j++)
			{
				particlecollision(i, j);
			}
		}
		//Calculates force in between particles
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + 1; j < 3; j++)
			{
				ForceCalculations(i, j);
			}
		}
		//Finds their accelaration, velocity, and increments their position for a time interval of 0.025 second.
		for (int j = 0; j < 3; j++)
		{
			if (mass[j] != 0)
			{
				accelaration[j].x = Force[j].x / mass[j];
				accelaration[j].y = Force[j].y / mass[j];
			}
			velocity[j].x = velocity[j].x + (accelaration[j].x * 0.025);
			velocity[j].y = velocity[j].y + (accelaration[j].y * 0.025);
			position[j].x = position[j].x + (velocity[j].x * 0.025);
			position[j].y = position[j].y + (velocity[j].y * 0.025);
		}
	}
	return;
}

//Calculates force among the 2 particles given to the function by their integer index in the array
void Simulate::ForceCalculations(int p1, int p2)
{
	//Fg is for gravitational force, Fq for electrostatic force, Fnet for total
	//coscomp for finding cosine of the angle, and sincomp for finding sin of the angle in between the particles
	double distance, Fg, Fq, Fnet, coscomp, sincomp, angle_of_action;
	//Calculates distance between the particles
	distance = sqrt(pow((position[p2].x - position[p1].x), 2) + pow((position[p2].y - position[p1].y), 2));
	//Gravitational force calculations
	Fg = (G * mass[p1] * mass[p2]) / (distance * distance);
	//Electrostatic force calculations
	Fq = -(K * charge[p1] * charge[p2]) / (distance * distance);
	//Net force calculations
	Fnet = Fg + Fq;
	//Finding the cos component of the force
	angle_of_action = atan(abs(position[p2].y - position[p1].y) / abs(position[p2].x - position[p1].x));
	fix_angle((position[p2].x - position[p1].x), (position[p2].y - position[p1].y), angle_of_action);
	coscomp = cos(angle_of_action);
	sincomp = sin(angle_of_action);
	//Calculating net force on each
	Force[p1].x = Force[p1].x + (Fnet * coscomp);
	Force[p1].y = Force[p1].y + (Fnet * sincomp);
	Force[p2].x = Force[p2].x - (Fnet * coscomp);
	Force[p2].y = Force[p2].y - (Fnet * sincomp);
}

//Checking and resolving wall collision of the particle
bool Simulate::wallcollision(int p)
{
	//If mass of a particle is 0, it is not taking part in the simulation, hence return false
	if (mass[p] == 0)
		return false;
	//Collision flag
	bool flag = false;
	//We need screen resolution to know the boundaries of screen
	GetScreenResolution get;
	//Checking on x axis (horizontally)
	if (position[p].x<20 || position[p].x>(get.get_width() - 20))
	{
		//We invert the velocity if there is a collision
		velocity[p].x = -velocity[p].x;
		//Set the collision flag to true
		flag = true;
		//Fix the position to the boundary if it goes further beyond
		if (position[p].x < 20)
			position[p].x = 20;
		if (position[p].x > (get.get_width() - 20))
			position[p].x = (get.get_width() - 20);
	}
	//Checking on y axis (vertically)
	if (position[p].y<20 || position[p].y>(get.get_height() - 20))
	{
		//We invert the velocity if there is a collision
		velocity[p].y = -velocity[p].y;
		//Set the collision flag to true
		flag = true;
		//Fix the position to the boundary if it goes further beyond
		if (position[p].y < 20)
			position[p].y = 20;
		if (position[p].y > (get.get_height() - 20))
			position[p].y = (get.get_height() - 20);
	}
	//Return flag
	return flag;
}

//This function is used for fixing angles in -pi to +pi range
void Simulate::fix_angle(double x, double y, double& angle)
{
	if (x == 0)
	{
		if (y >= 0)
			angle = M_PI / 2;
		else
			angle = -M_PI / 2;
		return;
	}
	//x<0 & y<0 implies third quadrant
	if (x < 0 && y < 0)
	{
		angle = -M_PI + angle;
	}
	//Implies second quadrant
	if (x < 0 && y >= 0)
	{
		angle = M_PI - angle;
	}
	//Implies fourth quadrant
	if (x > 0 && y < 0)
	{
		angle = -1 * angle;
	}
	//Default case is first quadrant and requires no correction
	return;
}

//Particle collision detection and resolution function
bool Simulate::particlecollision(int p1, int p2)
{
	double v1_magnitude, v2_magnitude, v1_angle, v2_angle, v1_shifted_angle, v2_shifted_angle, temp_velocity, v1_new_magnitude, v2_new_magnitude;
	Vector v1_shifted, v2_shifted;
	//Calculating magnitude of velocities
	v1_magnitude = sqrt((velocity[p1].x * velocity[p1].x) + (velocity[p1].y * velocity[p1].y));
	v2_magnitude = sqrt((velocity[p2].x * velocity[p2].x) + (velocity[p2].y * velocity[p2].y));
	//Calculating distance between particles
	double distance = sqrt(pow((position[p2].x - position[p1].x), 2) + pow((position[p2].y - position[p1].y), 2));
	//Checks collision, returns false if none
	if (distance > 40)
	{
		return false;
	}
	//Resolving any kind of overlap between particles in case of collision
	particle_collision_position_resolution(p1, p2);
	//For finding difference between their x coordinates and y coordinates
	double y_difference, x_difference, angle_of_collision;
	y_difference = position[p2].y - position[p1].y;
	x_difference = position[p2].x - position[p1].x;
	//Calculating angle of collision using arctangent, then fixing it with fix_angle function
	angle_of_collision = atan(abs(y_difference) / abs(x_difference));
	fix_angle(x_difference, y_difference, angle_of_collision);
	//Finding the angles of individual velocities and fixing them
	v1_angle = atan(abs(velocity[p1].y) / abs(velocity[p1].x));
	v2_angle = atan(abs(velocity[p2].y) / abs(velocity[p2].x));
	fix_angle(velocity[p1].x, velocity[p1].y, v1_angle);
	fix_angle(velocity[p2].x, velocity[p2].y, v2_angle);
	//Finding angles from the axis of collision for effective velocity calculations using momentum conservation along the axis of collision
	v1_shifted_angle = v1_angle - angle_of_collision;
	v2_shifted_angle = v2_angle - angle_of_collision;
	//Finding the velocity components along the new x and y axis
	v1_shifted.x = v1_magnitude * cos(v1_shifted_angle);
	v1_shifted.y = v1_magnitude * sin(v1_shifted_angle);
	v2_shifted.x = v2_magnitude * cos(v2_shifted_angle);
	v2_shifted.y = v2_magnitude * sin(v2_shifted_angle);
	//Momentum conservation calculations for new velocities
	temp_velocity = ((mass[p2] * v2_shifted.x) + (2 * mass[p1] * v1_shifted.x) - (mass[p1] * v2_shifted.x)) / (mass[p1] + mass[p2]);
	v1_shifted.x = ((mass[p1] * v1_shifted.x) + (2 * mass[p2] * v2_shifted.x) - (mass[p2] * v1_shifted.x)) / (mass[p1] + mass[p2]);
	v2_shifted.x = temp_velocity;
	//Finding the new angles still in the rotated system
	v1_shifted_angle = atan(abs(v1_shifted.y) / abs(v1_shifted.x));
	v2_shifted_angle = atan(abs(v2_shifted.y) / abs(v2_shifted.x));
	//Fixing those angles
	fix_angle(v1_shifted.x, v1_shifted.y, v1_shifted_angle);
	fix_angle(v2_shifted.x, v2_shifted.y, v2_shifted_angle);
	//Finding new magnitudes
	v1_new_magnitude = sqrt((v1_shifted.x * v1_shifted.x) + (v1_shifted.y * v1_shifted.y));
	v2_new_magnitude = sqrt((v2_shifted.x * v2_shifted.x) + (v2_shifted.y * v2_shifted.y));
	//Shifting the components back to the original angle system.
	velocity[p1].x = v1_new_magnitude * cos(v1_shifted_angle+angle_of_collision);
	velocity[p1].y = v1_new_magnitude * sin(v1_shifted_angle+angle_of_collision);
	velocity[p2].x = v2_new_magnitude * cos(v2_shifted_angle+angle_of_collision);
	velocity[p2].y = v2_new_magnitude * sin(v2_shifted_angle+angle_of_collision);
	//Returning true for collision detection and resolution
	return true;
}

//Resolution of particle collision overlaps
void Simulate::particle_collision_position_resolution(int p1, int p2)
{
	//Finding distance between the two particles
	double distance;
	distance = sqrt(pow((position[p2].x - position[p1].x), 2) + pow((position[p2].y - position[p1].y), 2));
	//Shifting them backwards in the direction they came from with the time interval 0.0025 (1/10th of the time we moved them forward in) until the overlap is completely resolves.
	while (distance < 40)
	{
		position[p1].x = position[p1].x - (velocity[p1].x * 0.0025);
		position[p1].y = position[p1].y - (velocity[p1].y * 0.0025);
		position[p2].x = position[p2].x - (velocity[p2].x * 0.0025);
		position[p2].y = position[p2].y - (velocity[p2].y * 0.0025);
		distance = sqrt(pow((position[p2].x - position[p1].x), 2) + pow((position[p2].y - position[p1].y), 2));
	}
	return;
}