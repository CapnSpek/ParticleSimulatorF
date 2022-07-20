//Header guards
#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

//For the definition of a Vector data type
class Vector
{
private:
	//Private double x and y values
	double x, y;
public:
	//Constructor for initialization
	Vector(double x=0, double y=0) :x(x), y(x) {}
	//Copy constructor
	Vector(const Vector& cop) :x(cop.x), y(cop.y) {}
	//Set function
	void set(double xx, double yy);
	//Addition operator overloading
	Vector  operator+(const Vector& other) const;
	//Subtraction operator overloading
	Vector operator-(const Vector& other) const;
	//Equals operator overloading
	void operator=(const Vector& other);
	//Used to obtain x
	double get_x();
	//Used to obtain y
	double get_y();
	//Input stream overloading
	friend std::istream& operator>>(std::istream& input, Vector& D);
	//Output stream overloading
	friend std::ostream& operator<<(std::ostream& output, const Vector& D);
	friend class Simulate;
};
//End header guards
#endif