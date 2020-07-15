#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "camera.h"

Camera::Camera() : mPos(0.0f,0.0f,0.0f),mViewCenter(0.0f,0.0f,-1.0f),mUp(0.0f,1.0f,0.0f),
mMoveLeft(false), mMoveRight(false), mMoveFoward(false), mMoveBackWord(false)
{

}

void Camera::Update(float deltaTime)
{
	//update everything
	//printf("%f\n", deltaTime);
	float moveSpeed = 10.0f;
	if (mMoveLeft)
	{
		//Vector3f moveDirection(-5.0, 0.0, 0.0);
		//moveDirection.Normalize();
		//mPos = mPos + moveDirection * moveSpeed*deltaTime;
		//mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
		////mPos.x -= moveSpeed * deltaTime;
		////mViewCenter.x -= moveSpeed * deltaTime;

		//rotate
		RotateView(moveSpeed*deltaTime, 0.0, 1.0, 0.0);
	}

	if (mMoveRight)
	{
		//Vector3f moveDirection(5.0, 0.0, 0.0); //3.0会影响速度，需要单位化
		//moveDirection.Normalize();
		//mPos = mPos + moveDirection * moveSpeed*deltaTime;
		//mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
		////mPos.x += moveSpeed * deltaTime;
		////mViewCenter.x += moveSpeed * deltaTime;

		//rotate
		RotateView(moveSpeed*deltaTime, 0.0, -1.0, 0.0);

	}

	if (mMoveFoward)
	{
		Vector3f moveDirection(0.0, 0.0, -1.0);
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
	}

	if (mMoveBackWord)
	{
		Vector3f moveDirection(0.0, 0.0, 1.0); //3.0会影响速度，需要单位化
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
	}

	//set modeview matrix
	gluLookAt(mPos.x, mPos.y, mPos.z,
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}

void Camera::RotateView(const float& angle, const float& x, const float& y, const float& z)
{
	Vector3f viewDirection = mViewCenter - mPos;
	Vector3f newDirection;
	float C = cos(angle);
	float S = sin(angle);

	Vector3f tempX = Vector3f(C + x * x*(1 - C), x*y*(1 - C) - z * S, x*z*(1 - C) + y * S);
	Vector3f tempY = Vector3f(x*y*(1-C) + z*S, C+y*y*(1-C), y*z*(1-C) - x*S);
	Vector3f tempZ = Vector3f(x*z*(1-C)-y*S, y*z*(1-C)+x*S, C+z*z*(1-C));
	newDirection.x = tempX * viewDirection;
	newDirection.y = tempY * viewDirection;
	newDirection.z = tempZ * viewDirection;

	mViewCenter = mPos + newDirection;
}
