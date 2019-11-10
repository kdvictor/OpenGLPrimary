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

//万向锁？？？？

void Camera::Update(float deltaTime)
{
	//update everything
	float moveSpeed = 0.1f;
	if (mIsMoveLeft)
	{
		//left direction vector
		////eye和view center要一起移动
		//Vector3f leftDirection(-1.0f, 0.0f, 0.0f);
		//leftDirection.Normalize(); // ????????
		//mEye = mEye + leftDirection * moveSpeed * deltaTime;
		//mViewCenter = mViewCenter + leftDirection * moveSpeed * deltaTime;
		mEye.x -= moveSpeed * deltaTime;
		mViewCenter.x -= moveSpeed * deltaTime;

		//左右旋转
		//Vector3f viewDirection = mViewCenter - mEye;
		//viewDirection.Normalize();
		//Vector3f rightDirection = viewDirection ^ mUp;
		//rightDirection.Normalize();
		//mEye = mEye + rightDirection * moveSpeed * deltaTime;
		//mViewCenter = mViewCenter + rightDirection * moveSpeed * deltaTime;
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
		Vector3f backWardDirection(mUp.x, mUp.y, mUp.z);
		backWardDirection.Normalize();
		mEye = mEye + backWardDirection * moveSpeed * deltaTime;
		mViewCenter = mViewCenter + backWardDirection * moveSpeed * deltaTime;
	}

	//set mode view matrix
	gluLookAt(mEye.x, mEye.y, mEye.z, 
		mViewCenter.x, mViewCenter.y, mViewCenter.z,
		mUp.x, mUp.y, mUp.z);
}

//rotate view direction 视线：eye->viewcenter
void Camera::RotateView_i(float angle, float x, float y, float z)
{
	Vector3f viewDirection = mViewCenter - mEye;
	Vector3f newDirection;
	float C = cosf(angle);
	float S = sinf(angle);

	Vector3f tempX(C + x * x*(1 - C), x*y*(1 - C) - z * S, x*z*(1 - C) + y * S);
	newDirection.x = tempX * viewDirection;

	Vector3f tempY(x*y*(1 - C) + z * S, C + y * y*(1 - C), y*z*(1 - C) - x * S);
	newDirection.y = tempY * viewDirection;

	Vector3f tempZ(x*z*(1 - C) - y * S, y*z*(1 - C) + x * S, C + z * z*(1 - C));
	newDirection.z = tempZ * viewDirection;

	//旋转主要是改变 viewcenter的位置
	mViewCenter = mEye + newDirection;
}

void Camera::Pitch(float angele)
{
	//计算向右的向量
	Vector3f viewDirection = mViewCenter - mEye;
	viewDirection.Normalize();

	mUp.Normalize();
	Vector3f rightDirection = viewDirection ^ mUp;
	rightDirection.Normalize();
	RotateView_i(angele, rightDirection.x, rightDirection.y, rightDirection.z);
}


LH_NAMESPACE_END