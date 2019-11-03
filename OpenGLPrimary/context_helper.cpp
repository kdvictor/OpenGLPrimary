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

LH_NAMESPACE_END