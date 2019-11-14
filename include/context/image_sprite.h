/*
==============================
*Copyright(c), huan.liu, 2019
*All rights reversed

*Author:huanliu_uestc@163.com

*FileName:image_sprite.h
*Brief: image sprite:”√”⁄ªÊ÷∆2D

*Date: 2019.11.14
==============================
*/

#ifndef __IMAGE_SPRITR_H__
#define __IMAGE_SPRITR_H__

#include <windows.h>
#include <gl/GL.h>
#include "common_macrosh.h"
#include "context/texture.h"
#include "context/vector3f.h"

LH_NAMESPACE_BEGIN


class LH_EXPORT ImageSprite
{
public:
	void SetTexture(Texture* const& texture);

	void SetRect(const float& x, const float& y, const float& width, const float& height);

	void Draw();

	Vector3f mMesh[4];

	Texture* mTexture;

};

LH_NAMESPACE_END

#endif