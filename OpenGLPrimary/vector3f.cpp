#include "context/vector3f.h"

LH_NAMESPACE_BEGIN


Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f Vector3f::operator*(const float& scaler)
{
	return Vector3f(x*scaler, y*scaler, z*scaler);
}

Vector3f Vector3f::operator+(const Vector3f& vector)
{
	return Vector3f(x + vector.x, y + vector.y, z + vector.z);
}

 void Vector3f::operator=(const Vector3f& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
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
	 return sqrtf(x*x + y * y + z * z);
 }

LH_NAMESPACE_END