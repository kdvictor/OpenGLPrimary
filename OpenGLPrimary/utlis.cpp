#include <stdio.h>
#include "utlis.h"

unsigned char * LoadFileContent(const char * const & pFilePath)
{
	unsigned char* pFileContent = nullptr;
	FILE* pFile = nullptr;
	fopen_s(&pFile, pFilePath, "rb");
	if (pFile == nullptr)
	{
		return pFileContent;
	}

	fseek(pFile, 0, SEEK_END); //移至文件末尾
	int len = ftell(pFile); //取得长度
	if (len > 0)
	{
		rewind(pFile); //移至头部
		pFileContent = new unsigned char[len + 1];
		fread(pFileContent, sizeof(unsigned char), len, pFile);
		pFileContent[len] = '\0';
	}

	fclose(pFile);

	//printf("%s\n", pFileContent);
	return pFileContent;
}

unsigned char * DecodeBMP(unsigned char * const & pFileContent, int & width, int & height)
{
	unsigned char* pPixelData = nullptr;
	if (pFileContent == nullptr)
	{
		return pPixelData;
	}

	int pixelDataOffeset = *((int*)(pFileContent + 10));
	width = *((int*)(pFileContent + 18));
	height = *((int*)(pFileContent + 22));
	pPixelData = (unsigned char*)(pFileContent + pixelDataOffeset);
	if (pPixelData == nullptr)
	{
		//日志
		return pPixelData;
	}

	//bgr -> rgb
	for (int i = 0; i < width*height*3; i += 3)
	{
		pPixelData[i] = pPixelData[i] ^ pPixelData[i + 2];
		pPixelData[i+2] = pPixelData[i] ^ pPixelData[i + 2];
		pPixelData[i] = pPixelData[i] ^ pPixelData[i + 2];
	}

	return pPixelData;
}
