#include "Vector.h"
using namespace std;
void Vector::set(double xx, double yy)
{
	x = xx;
	y = yy;
	return;
}
Vector Vector::operator+(const Vector& other) const
{
	return Vector((x + other.x), (y + other.y));
}
Vector Vector::operator-(const Vector& other) const
{
	return Vector((x - other.x), (y - other.y));
}
void Vector::operator=(const Vector& other)
{
	x = other.x;
	y = other.y;
	return;
}
double Vector::get_x()
{
	return x;
}
double Vector::get_y()
{
	return y;
}
istream& operator>>(istream& input, Vector& V)
{
	input >> V.x >> V.y;
	return input;
}
ostream& operator<<(ostream& output, const Vector& D)
{
	output << D.x << " " << D.y;
	return output;
}