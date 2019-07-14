/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_point.h
*Brief: render point

*Date: 2019.7.15
==============================
*/

#ifndef COMMAND_RENDER_POINT_H_
#define COMMAND_RENDER_POINT_H_

#include "common_macrosh.h"
#include "command_render_base.h"

LH_NAMESPACE_BEGIN

class RenderPointCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif