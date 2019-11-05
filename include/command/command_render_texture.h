/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_texture.h
*Brief: render texture

*Date: 2019.11.4
==============================
*/

#ifndef __COMMAND_RENDER_TEXTURE_H__
#define __COMMAND_RENDER_TEXTURE_H__

#include "common_macrosh.h"
#include "command/command_render_base.h"
#include "context/texture.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderTextureCommand : public RenderCommandBase
{
public:
	virtual void Render();
	virtual void Init_i();

private:
	Texture mTexture;
};

LH_NAMESPACE_END

#endif