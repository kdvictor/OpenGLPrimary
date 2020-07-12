#include "texture.h"
#include "utlis.h"

void Texture::Init(const char * const & pFilePath)
{
	unsigned char* pFileContent = nullptr;
	pFileContent = LoadFileContent(pFilePath);
	if (pFilePath == nullptr)
	{
		//»’÷æ
	}



}
