/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_base.h
*Brief: base render command

*Date: 2019.7.15
==============================
*/

#ifndef COMMAND_BASE_H_
#define COMMAND_BASE_H_

#include "common_macrosh.h"
#include "common.h"

LH_NAMESPACE_BEGIN

class RenderCommandBase
{
public:
	virtual void Render();

public:
	static void Init();
};

LH_NAMESPACE_END

#endif

