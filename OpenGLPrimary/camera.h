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
};