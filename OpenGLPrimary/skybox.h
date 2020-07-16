#pragma once
#include "texture.h"
class SkyBox
{
public:
	void Init(const char* const& pFolderPath);
	void Draw(const int& x, const int& y, const int& z);
public:
	Texture *mFront, *mBack, *mLeft, *mRight, *mTop, *mBottom;
};