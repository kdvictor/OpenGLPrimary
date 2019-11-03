/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_quads.h
*Brief: render quads

*Date: 2019.11.3
==============================
*/

#ifndef __COMMAND_RENDER_QUADS_H__
#define  __COMMAND_RENDER_QUADS_H__

#include "common_macrosh.h"
#include "command/command_render_base.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderQuadsCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif