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
};