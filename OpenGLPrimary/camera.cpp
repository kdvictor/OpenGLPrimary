#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "context/camera.h"

LH_NAMESPACE_BEGIN

Camera::Camera() : mEye(0.0f,0.0f,0.0f), 
mViewCenter(0.0f,0.0f,-1.0f), 
mUp(0.0f,1.0f,0.0f),
mIsMoveLeft(false),
mIsMoveRight(false),
mIsMoveForward(false),
mIsMoveBackward(false)
{

}

void Camera::Update(float deltaTime)
{
	//update everything
	float moveSpeed = 1.0f;
	if (mIsMoveLeft)
	{
		//left direction vector
		//eye和view center要一起移动
		Vector3f leftDirection(-1.0f, 0.0f, 0.0f);
		leftDirection.Normalize(); // ????????
		mEye = mEye + leftDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + leftDirection * moveSpeed * deltaTime;
		//mEye.x -= moveSpeed * deltaTime;
		//mViewCenter.x -= moveSpeed * deltaTime;
	}

	if (mIsMoveRight)
	{
		Vector3f rightDirection(1.0f, 0.0f, 0.0f);
		rightDirection.Normalize();
		mEye = mEye + rightDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + rightDirection * moveSpeed * deltaTime;
		//mEye.x += moveSpeed * deltaTime;
		//mViewCenter.x += moveSpeed * deltaTime;
	}

	if (mIsMoveForward)
	{
		Vector3f forwardDirection(0.0f, 0.0f, -1.0f);
		forwardDirection.Normalize();
		mEye = mEye + forwardDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + forwardDirection * moveSpeed * deltaTime;
	}

	if (mIsMoveBackward)
	{
		Vector3f backWardDirection(0.0f, 0.0f, 1.0f);
		backWardDirection.Normalize();
		mEye = mEye + backWardDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + backWardDirection * moveSpeed * deltaTime;
	}

	//set mode view matrix
	gluLookAt(mEye.x, mEye.y, mEye.z, 
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}


LH_NAMESPACE_END