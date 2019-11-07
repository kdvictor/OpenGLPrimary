#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "context/camera.h"

LH_NAMESPACE_BEGIN

Camera::Camera() : mEye(0.0f,0.0f,0.0f), 
mViewCenter(0.0f,0.0f,-1.0f), 
mUp(0.0f,1.0f,0.0f),
mIsMoveLeft(false),
mIsMoveRight(false)
{

}

void Camera::Update(float deltaTime)
{
	//update everything
	float moveSpeed = 10.0f;
	if (mIsMoveLeft)
	{
		mEye.x -= moveSpeed * deltaTime;
		mViewCenter.x -= moveSpeed * deltaTime;
	}

	if (mIsMoveRight)
	{
		mEye.x += moveSpeed * deltaTime;
		mViewCenter.x += moveSpeed * deltaTime;
	}

	//set mode view matrix
	gluLookAt(mEye.x, mEye.y, mEye.z, 
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}


LH_NAMESPACE_END