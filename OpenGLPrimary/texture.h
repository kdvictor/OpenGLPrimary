#pragma once
#include <windows.h>
#include<gl/GL.h> //要使用这个库必须包含<windows.h>
#include <unordered_map>

class Texture
{
protected:
	void Init(const char* const& pFilePath, bool invertY);
public:
	GLuint mTextureId;
	std::string mFilePath;
	static Texture* LoadTexture(const char* const& pFilePath, bool invertY = true);
	static void UnLoadTexture(const Texture*& ptexture);
	static std::unordered_map<std::string, Texture*> mTextures;
};
