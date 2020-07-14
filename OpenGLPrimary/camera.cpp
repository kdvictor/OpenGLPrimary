#include <windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "camera.h"

Camera::Camera() : mPos(0.0f,0.0f,0.0f),mViewCenter(0.0f,0.0f,-1.0f),mUp(0.0f,1.0f,0.0f),
mMoveLeft(false), mMoveRight(false)
{

}

void Camera::Update(float deltaTime)
{
	//update everything
	//printf("%f\n", deltaTime);
	float moveSpeed = 10.0f;
	if (mMoveLeft)
	{
		Vector3f moveDirection(-5.0,0.0,0.0);
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
		//mPos.x -= moveSpeed * deltaTime;
		//mViewCenter.x -= moveSpeed * deltaTime;
	}

	if (mMoveRight)
	{
		Vector3f moveDirection(5.0, 0.0, 0.0); //3.0会影响速度，需要单位化
		moveDirection.Normalize();
		mPos = mPos + moveDirection * moveSpeed*deltaTime;
		mViewCenter = mViewCenter + moveDirection * moveSpeed*deltaTime;
		//mPos.x += moveSpeed * deltaTime;
		//mViewCenter.x += moveSpeed * deltaTime;
	}

	//set modeview matrix
	gluLookAt(mPos.x, mPos.y, mPos.z,
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}
