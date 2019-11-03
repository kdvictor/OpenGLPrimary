/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_tringlestrip.h
*Brief: render tringle strip

*Date: 2019.11.3
==============================
*/

#ifndef __COMMAND_RENDER_TRINGLESTRIP_H__
#define  __COMMAND_RENDER_TRINGLESTRIP_H__

#include "common_macrosh.h"
#include "command/command_render_base.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderTringleStripCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif