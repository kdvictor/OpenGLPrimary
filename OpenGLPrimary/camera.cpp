#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "camera.h"

Camera::Camera() : mPos(0.0f,0.0f,5.0f),mViewCenter(0.0f,0.0f,1.0f),mUp(0.0f,1.0f,0.0f),
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
		/********************万向锁（查）四元素**************************/
		Vector3f viewDirection = mViewCenter - mPos;
		viewDirection.Normalize();
		Vector3f moveDirection = mUp^viewDirection;
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;

		//rotate
		//RotateView(moveSpeed*deltaTime, 0.0, 1.0, 0.0);
	}

	if (mMoveRight)
	{
		Vector3f viewDirection = mViewCenter - mPos;
		viewDirection.Normalize();
		Vector3f moveDirection = viewDirection^mUp; //3.0会影响速度，需要单位化
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;

		//rotate
		//RotateView(moveSpeed*deltaTime, 0.0, -1.0, 0.0);

	}

	if (mMoveFoward)
	{
		Vector3f moveDirection = mViewCenter - mPos;
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
	}

	if (mMoveBackWord)
	{
		Vector3f moveDirection = mPos - mViewCenter; //3.0会影响速度，需要单位化
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

void Camera::Pitch(const float& angle)
{
	//right direction vector
	Vector3f rightDirection;
	Vector3f viewerDirection = mViewCenter - mPos;
	viewerDirection.Normalize();
	rightDirection = viewerDirection ^ mUp;
	rightDirection.Normalize();

	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}

void Camera::Yam(const float & angle)
{
	mUp.Normalize();
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}

void Camera::SwitchTo2D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-viewPortWidth / 2, viewPortWidth / 2, -viewPortHeight / 2, viewPortHeight / 2);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::SwitchTo3D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, (float)viewPortWidth / (float)viewPortHeight, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
}