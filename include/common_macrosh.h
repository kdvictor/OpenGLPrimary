/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:common_macros.h
*Brief: common macros

*Date: 2019.7.15
==============================
*/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#ifndef LH_NAMESPACE_BEGIN
#define LH_NAMESPACE_BEGIN\
	namespace LH{
#endif

#ifndef LH_NAMESPACE_END
#define LH_NAMESPACE_END }
#endif

#ifndef LH_EXPORT
#define LH_EXPORT _declspec(dllexport)
#endif


#ifndef DEL_PTR
#define DEL_PTR(ptr)        \
	do                      \
	{                       \
		if (ptr != nullptr) \
		{                   \
			delete (ptr);   \
			ptr = nullptr;  \
		}                   \
	} while (false)
#endif

#endif COMMON_MACROS_H_



