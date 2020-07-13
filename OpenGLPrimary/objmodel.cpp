#include <stdio.h>
#include <string>
#include <sstream>
#include "objmodel.h"
#include "utlis.h"

void ObjModel::Init(const char * const & pFilePath)
{
	unsigned char* pFileContent = LoadFileContent(pFilePath);
	if (pFileContent == nullptr)
	{
		//ÈÕÖ¾
	}

	std::stringstream ssFileContent((char*)pFileContent);
	char szOneLine[256];
	while(!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256 * sizeof(char));
		ssFileContent.getline(szOneLine, 256);
		//printf(">%s\n", szOneLine);
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				if (szOneLine[1] == 't')
				{
					printf("vt>%s\n", szOneLine);
				}
				else if(szOneLine[1] == 'n')
				{
					printf("vn>%s\n", szOneLine);
				}
				else
				{
					printf("v>%s\n", szOneLine);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				printf("f>%s\n", szOneLine);
			}
		}
	}

}

void ObjModel::Draw()
{

}
