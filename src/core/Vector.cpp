
#include "common.hpp"
#include "Vector.hpp" 

#include <cmath>

using namespace std; 

Vector::Vector() 
{
	x = y = z  = w = 0.0;
	column = true;
}

Vector::Vector(float x1, float y1, float z1, float w1) 
{
	column = true; 
	x = x1; 
	y = y1; 
	z = z1; 
	w = w1;
}
Vector::Vector(float x1, float y1, float z1) : Vector(x1, y1, z1, 1)
{
}

Vector::Vector(float x1, float y1, float z1, float w1, bool column1) 
{
	column = column1;
	x = x1;
	y = y1; 
	z = z1; 
	w = w1; 
}

Vector::Vector(float a) 
{
	column = true; 
	x = a; 
	y = a; 
	z = a; 
	w = a; 
}

Vector& Vector::operator= (Vector v) 
{
	x = v.getX();
	y = v.getY(); 
	z = v.getZ();
	w = v.getW();
	column = v.isColumn();
}

Vector& Vector::operator+ (Vector v) 
{
	return *(new Vector(x + v.getX(), y + v.getY(), z + v.getZ(), w + v.getW(), column));
}
Vector& Vector::operator- (Vector v) 
{
	return *(new Vector(x - v.getX(), y - v.getY(), z - v.getZ(), w - v.getW(), column));
}

bool Vector::operator==(Vector v) 
{
	return v.getX() == getX() && v.getY() == getY() && v.getZ() == getZ() && v.getW() == getW();
}

bool Vector::operator!=(Vector v) 
{
	return v.getX() != getX() || v.getY() != getY() || v.getZ() != getZ() || v.getW() == getW();
}
	
float Vector::dot(Vector v) 
{
	return x*v.getX() + y*v.getY() + z*v.getZ() + w*v.getW();
}

Vector Vector::cross(Vector v)
{
	return Vector(
		y*v.getZ() - z*v.getY(),
		z*v.getX() - x*v.getZ(),
		x*v.getY() - y*v.getX(),
		w
	);
}

Vector Vector::transpose() 
{
	return Vector(x,y,z,w,!column);
}

Vector Vector::normalized() 
{
	float l = sqrt(x*x + y*y + z*z);
	if (l>0) return Vector(x/l, y/l, z/l, w);
	else return Vector(0,0,0,0);
}

float Vector::getX() 
{
	return x;
}

float Vector::getY() 
{
	return y; 
}

float Vector::getZ() 
{
	return z;
}

float Vector::getW() 
{
	return w; 
}

bool Vector::isColumn() 
{
	return column;
}

Vector Vector::zero() 
{
	return Vector(0.0);
}
