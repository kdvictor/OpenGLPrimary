/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_objmodel.h
*Brief: render objmodel

*Date: 2019.11.5
==============================
*/

#ifndef __COMMAND_RENDER_OBJMODEL_H__
#define __COMMAND_RENDER_OBJMODEL_H__

#include <windows.h>
#include <gl/GL.h>
#include "common_macrosh.h"
#include "command/command_render_base.h"
#include "context/objmodel.h"
#include "context/texture.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderObjModelCommand : public RenderCommandBase
{
public:
	virtual void Render();

	virtual void Init_i();

private:
	ObjModel mObjModel;
	Texture mTexture;
};

LH_NAMESPACE_END

#endif