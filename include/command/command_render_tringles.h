/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_tringles.h
*Brief: render tringles

*Date: 2019.7.18
==============================
*/

#ifndef COMMAND_RENDER_TRINGLES_H_
#define  COMMAND_RENDER_TRINGLES_H_

#include "common_macrosh.h"
#include "command/command_render_base.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderTringlesCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif