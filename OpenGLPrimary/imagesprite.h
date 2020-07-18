#pragma once
#include "texture.h"
#include "vector3f.h"
class ImageSprite
{
public:
	Texture* mTexture;
	Vector3f mMesh[4];
	void SetTexture(Texture* texture);
	void SetRect(const float& centerX, const float& centerY, const float& width, const float& height);
	void Draw();
};