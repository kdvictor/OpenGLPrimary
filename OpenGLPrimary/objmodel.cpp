#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "objmodel.h"
#include "utlis.h"

typedef struct FloatData
{
	float v[3];
}FloatData;

void ObjModel::Init(const char * const & pFilePath)
{
	unsigned char* pFileContent = LoadFileContent(pFilePath);
	if (pFileContent == nullptr)
	{
		//»’÷æ
	}

	std::stringstream ssFileContent((char*)pFileContent);
	std::string temp;
	char szOneLine[256];
	std::vector<FloatData> positions, normals, texcoords;

	while(!ssFileContent.eof())
	{
		memset(szOneLine, 0, 256 * sizeof(char));
		ssFileContent.getline(szOneLine, 256);
		//printf(">%s\n", szOneLine);
		if (strlen(szOneLine) > 0)
		{
			if (szOneLine[0] == 'v')
			{
				std::stringstream ssOneLine(szOneLine);
				FloatData data;
				memset(&data, 0, sizeof(FloatData));
				if (szOneLine[1] == 't')
				{
					ssOneLine >> temp;
					ssOneLine >> data.v[0];
					ssOneLine >> data.v[1];
					texcoords.push_back(data);
					printf("texcoord:%f,%f\n", data.v[0], data.v[1]);
				}
				else if(szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					ssOneLine >> data.v[0];
					ssOneLine >> data.v[1];
					ssOneLine >> data.v[2];
					normals.push_back(data);
					printf("normal:%f,%f,%f\n", data.v[0], data.v[1],data.v[2]);
				}
				else
				{
					ssOneLine >> temp;
					ssOneLine >> data.v[0];
					ssOneLine >> data.v[1];
					ssOneLine >> data.v[2];
					positions.push_back(data);
					printf("position:%f,%f,%f\n", data.v[0], data.v[1], data.v[2]);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::stringstream ssOneLine(szOneLine);
				printf("f>%s\n", szOneLine);
			}
		}
	}

}

void ObjModel::Draw()
{

}
