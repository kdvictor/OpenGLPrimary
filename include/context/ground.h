/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:ground.h
*Brief: ground mdoel

*Date: 2019.11.15
==============================
*/

#ifndef __GROUND_H__
#define __GROUND_H__

#include <windows.h>
#include "gl/GL.h"
#include "common_macrosh.h"


LH_NAMESPACE_BEGIN

class LH_EXPORT Ground
{
public:
	void Init();

	void Draw();

	GLuint mGround;
};

LH_NAMESPACE_END

#endif