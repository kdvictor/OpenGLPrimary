/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:fbxmodel.h
*Brief: fbxmodel

*Date: 2019.11.17
==============================
*/

#ifndef __FBXMODEL_H__
#define __FBXMODEL_H__

#include <windows.h>
#include "gl/GL.h"
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT FBXModel
{
public:
	void Init(const char* const& filePath);

	void Draw();
};

LH_NAMESPACE_END

#endif