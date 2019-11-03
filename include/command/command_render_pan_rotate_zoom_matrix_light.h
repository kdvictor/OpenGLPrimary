/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:command_render_pan_rotate_zoom_matrix_light.h
*Brief: pan rotate zoom matrix light

*Date: 2019.11.3
==============================
*/

#ifndef __COMMAND_PAN_ROTATE_ZOOM_MATRIX_LIGHT_H__
#define  __COMMAND_PAN_ROTATE_ZOOM_MATRIX_LIGHT_H__

#include "common_macrosh.h"
#include "command/command_render_base.h"

LH_NAMESPACE_BEGIN

class LH_EXPORT RenderPanRotateZoomMatrixLightCommand : public RenderCommandBase
{
public:
	virtual void Render();
};

LH_NAMESPACE_END

#endif