#include "context/texture.h"
#include "context/context_helper.h"
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

void Texture::Init(const char* pImagePath)
{
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//生成纹理并存入显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pBmpData);

	glBindTexture(GL_TEXTURE_2D, 0);

	DEL_PTR(pImageContent);
}

LH_NAMESPACE_END