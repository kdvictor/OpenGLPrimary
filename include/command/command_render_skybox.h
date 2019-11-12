/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_skybox.h
*Brief: render skybox

*Date: 2019.11.5
==============================
*/

#ifndef __COMMAND_RENDER_SKYBOX_H__
#define __COMMAND_RENDER_SKYBOX_H__

#include <windows.h>
#include <gl/GL.h>
#include "common_macrosh.h"
#include "command/command_render_base.h"
#include "context/skybox.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderSkyBoxCommand : public RenderCommandBase
{
public:
	~RenderSkyBoxCommand();

	virtual void Render();

	virtual void Init_i();

public:
	inline void SetCameraPosition(const float& x, const float& y, const float& z)
	{
		mX = x;
		mY = y;
		mZ = z;
	}

private:
	SkyBox* mSkyBox;

private:
	float mX; //ÉãÏñ»úµÄÎ»ÖÃ
	float mY;
	float mZ;
};

LH_NAMESPACE_END

#endif