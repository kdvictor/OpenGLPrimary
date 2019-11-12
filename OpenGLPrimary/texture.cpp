#include "context/texture.h"
#include "context/context_helper.h"
#include "common_macrosh.h"

#include "soil.h"
#pragma comment(lib, "soil.lib")

LH_NAMESPACE_BEGIN

void Texture::Init(const char* pImagePath)
{
	/*******************第一种方式加载**********************/
	mTextureId = SOIL_load_OGL_texture(pImagePath, 0, 0, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_INVERT_Y);
	mImagePath = pImagePath;
	return;

	/*******************第二种方式加载**********************/
	//加载图片内容
	unsigned char* pImageContent = nullptr;
	pImageContent = ContextHelper::LoadFileContent(pImagePath);
	if (pImageContent == nullptr)
	{
		//log
		return;
	}

	//解码图片  -12.30
	unsigned char* pBmpData = nullptr;
	int width = 0;
	int height = 0;
	pBmpData = ContextHelper::DecodeBMP(pImageContent, width, height);//解码成像素
	if (pBmpData == nullptr)
	{
		//log
		return;
	}

	//生成纹理
	glGenTextures(1, &mTextureId);//申请一个纹理
	glBindTexture(GL_TEXTURE_2D, mTextureId); //设置当前纹理
	//操作当前纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //放大缩小过滤方式：线性过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);//纹理坐标0-1，超过部分的处理方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);//repeated模式：1.1和0.1取得像素一样，一次类推

	//生成纹理并存入显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pBmpData);

	glBindTexture(GL_TEXTURE_2D, 0);

	DEL_PTR(pImageContent);
}

/**************************************************************************/

std::unordered_map<std::string, Texture*> Texture::mTextures;

Texture* Texture::LoadTextures(const char* pImagePath)
{
	if (mTextures.find(pImagePath) != mTextures.end())
	{
		return mTextures[pImagePath];
	}

	auto pTexture = new Texture();
	pTexture->Init(pImagePath);
	mTextures.insert(std::make_pair(pImagePath, pTexture));
	return pTexture;
}

void Texture::UnLoadTextures(Texture* pTexture)
{
	auto iter = mTextures.find(pTexture->mImagePath);
	if (iter != mTextures.end())
	{
		mTextures.erase(pTexture->mImagePath);
		glDeleteTextures(1, &(iter->second->mTextureId));
		delete pTexture;
	}
}

LH_NAMESPACE_END