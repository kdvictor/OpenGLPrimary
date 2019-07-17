/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_line_loop.h
*Brief: render line

*Date: 2019.7.18
==============================
*/

#ifndef COMMAND_RENDER_LINE_LOOP_H_
#define  COMMAND_RENDER_LINE_LOOP_H_

#include "common_macrosh.h"
#include "command/command_render_base.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderLineLoopCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif