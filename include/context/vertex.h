/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:vertex.h
*Brief: vertex model

*Date: 2019.11.5
==============================
*/

#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT VertexData
{
public:
	float mPosition[3];
	float mNormal[3];
	float mTexcoord[2];
};

LH_NAMESPACE_END

#endif