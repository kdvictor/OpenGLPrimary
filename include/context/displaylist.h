/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:displaylist.h
*Brief: displaylist

*Date: 2019.11.13
==============================
*/

#ifndef __DISPLAYLIST_H__
#define __DISPLAYLIST_H__

#include <windows.h>
#include <gl/GL.h>
#include <functional>
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT DisplayList
{
public:
	GLuint mDisplayList;

	void Init(std::function<void()> foo);

	void Draw();
};

LH_NAMESPACE_END

#endif