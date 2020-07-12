#pragma once
#include <windows.h>
#include<gl/GL.h> //要使用这个库必须包含<windows.h>

class Texture
{
public:
	void Init(const char* const& pFilePath);

	GLuint mTextureId;
};
