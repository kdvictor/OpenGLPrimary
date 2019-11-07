/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:camera.h
*Brief: camera

*Date: 2019.11.7
==============================
*/

#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

#include "context/vector3f.h"
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT Camera
{
public:
	Camera();

public:
	Vector3f mEye;
	Vector3f mViewCenter;
	Vector3f mUp;

public:
	void Update(float deltaTime);
};

LH_NAMESPACE_END

#endif