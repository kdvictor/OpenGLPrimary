#include <math.h>
#include "vector3f.h"

Vector3f::Vector3f(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f Vector3f::operator*(const float& scale)
{
	return Vector3f(x*scale, y*scale, z*scale);
}

Vector3f Vector3f::operator+(const Vector3f& v)
{
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

void Vector3f::operator=(const Vector3f& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

void Vector3f::Normalize()
{
	float len = Magnitude();
	x /= len;
	y /= len;
	z /= len;
}

float Vector3f::Magnitude()
{
	return sqrt(x*x + y*y + z*z);
}
