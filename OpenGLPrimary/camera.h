#pragma once
#include "vector3f.h"

class Camera
{
public:
	Camera();
	void Update(float deltaTime);
public:
	Vector3f mPos, mViewCenter, mUp;
	bool mMoveLeft, mMoveRight, mMoveFoward, mMoveBackWord;

protected:
	void RotateView(const float& angle, const float& x, const float& y, const float& z);
};