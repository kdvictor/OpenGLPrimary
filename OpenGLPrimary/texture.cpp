#include "texture.h"
#include "utlis.h"

void Texture::Init(const char * const & pFilePath)
{
	//load file content
	unsigned char* pFileContent = nullptr;
	pFileContent = LoadFileContent(pFilePath);
	if (pFilePath == nullptr)
	{
		//日志
	}

	//decode data
	unsigned char* pPixelData = nullptr;
	int width = 0;
	int height = 0;
	pPixelData = DecodeBMP(pFileContent, width, height);
	if (pPixelData == nullptr)
	{
		//日志
	}

	//生成纹理
	glGenTextures(1, &mTextureId); //生成1张纹理
	glBindTexture(GL_TEXTURE_2D, mTextureId); //设置当前纹理
	//设置纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pPixelData); //将数据传入显卡
	glBindTexture(GL_TEXTURE_2D, 0); //用完将纹理设置为0

	//delete[] pFileContent; pFileContent = nullptr;
	return;
}
