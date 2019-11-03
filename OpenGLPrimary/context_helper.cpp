#include <stdio.h>

#include "context/context_helper.h"

LH_NAMESPACE_BEGIN

unsigned char* ContextHelper::LoadFileContent(const char* pFilePath)
{
	unsigned char* pFileContent = nullptr;
	FILE* pFile = fopen(pFilePath, "rb"); //read binary
	if (pFile == nullptr)
	{
		//log
		return nullptr;
	}

	//read
	fseek(pFile, 0, SEEK_END);
	int nLen = ftell(pFile);
	if (nLen > 0)
	{
		rewind(pFile);
		pFileContent = new unsigned char[nLen + 1];
		fread(pFileContent, sizeof(unsigned char), nLen, pFile);
		pFileContent[nLen] = '\0';
	}

	fclose(pFile);

	return pFileContent;
}

unsigned char* ContextHelper::DecodeBMP(unsigned char* bmpFileData, int& width, int& height)
{
	unsigned char* pPixelData = nullptr;

	if (0x4D42 == *((unsigned short*)bmpFileData)) //ÅÐ¶ÏÊÇ²»ÊÇbmpÍ¼Ïñ
	{
		int pixelDataOffset = *((int*)(bmpFileData + 10));
		width = *((int*)(bmpFileData + 18));
		height = *((int*)(bmpFileData + 22));
		pPixelData = bmpFileData + pixelDataOffset;
		if (pPixelData == nullptr)
		{
			//log
			return nullptr;
		}

		//bgr->rgb
		for (int i = 0; i < width*height*3; i+=3)
		{
			pPixelData[i] = pPixelData[i] ^ pPixelData[i + 2];
			pPixelData[i + 2] = pPixelData[i] ^ pPixelData[i + 2];
			pPixelData[i] = pPixelData[i] ^ pPixelData[i + 2];
		}
	}

	return pPixelData;
}

LH_NAMESPACE_END