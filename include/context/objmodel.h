/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:objmodel.h
*Brief: objmodel

*Date: 2019.11.5
==============================
*/

#ifndef __OBJMODEL_H__
#define __OBJMODEL_H__

#include "common_macrosh.h"
#include "context/vertex.h"

LH_NAMESPACE_BEGIN

struct ObjOneLineData
{
	float v[3];
};

class LH_EXPORT ObjModel
{
public:
	void Init(const char* objModel);

public:
	VertexData* mVertexes;

	int* mIndices;

};

LH_NAMESPACE_END

#endif