#pragma once



class Vector3f
{
public:
	union 
	{
		struct 
		{
			float x, y, z;
		};

		float v[3];
	};
	Vector3f(const float& x, const float& y, const float& z);
	Vector3f operator*(const float& scale);
	Vector3f operator+(const Vector3f& v);
	void operator=(const Vector3f& v);
	void Normalize();
	float Magnitude();
};