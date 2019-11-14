/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:list.h
*Brief: list mdoel

*Date: 2019.11.14
==============================
*/

#ifndef __LIST_H__
#define __LIST_H__

#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT List
{
public:
	void* mNext;
	template<typename T>
	T* Next()
	{
		return (T*)mNext;
	}
};

LH_NAMESPACE_END

#endif