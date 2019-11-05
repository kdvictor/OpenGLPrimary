/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:context_helper.h
*Brief: context helper

*Date: 2019.11.3
==============================
*/

#ifndef __COMMAND_CONTEXTHELPER_H__
#define  __COMMAND_CONTEXTHELPER_H__

#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT ContextHelper
{
public:
	static unsigned char* LoadFileContent(const char* pFilePath);

	static unsigned char* DecodeBMP(unsigned char* bmpFileData, int& width, int& height);
};

LH_NAMESPACE_END

#endif