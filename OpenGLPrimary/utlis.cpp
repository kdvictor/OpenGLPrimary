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

	printf("%s\n", pFileContent);
	return pFileContent;
}
