#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include "context/objmodel.h"
#include "context/context_helper.h"

LH_NAMESPACE_BEGIN

void ObjModel::Init(const char* objModel)
{
	unsigned char* pFileContent = ContextHelper::LoadFileContent(objModel);
	//找出有用的信息，V:顶点 Vt:纹理坐标 Vn：法线，f: face 
	std::stringstream ssFileContent((char*)pFileContent);
	char onlineContent[256]; //一行数据
	std::string temp;
	std::vector<ObjOneLineData> positions, texttures, normals;

	while (!ssFileContent.eof())
	{
		memset(onlineContent, 0, 256);
		ssFileContent.getline(onlineContent, 256);

		if (strlen(onlineContent) > 0) //空行不读
		{
			std::stringstream ssObjOneLine(onlineContent);
			switch (*onlineContent)
			{
			case 'v':
				if (*(onlineContent + 1) == 't')
				{
					ssObjOneLine >> temp;
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					positions.push_back(data);
					printf("texure:%f, %f\n", data.v[0], data.v[1]);
				}
				else if(*(onlineContent + 1) == 'n')
				{
					ssObjOneLine >> temp;
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					ssObjOneLine >> data.v[2];
					normals.push_back(data);
					printf("normal:%f, %f, %f\n", data.v[0], data.v[1], data.v[2]);
				}
				else
				{
					ssObjOneLine >> temp;
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					ssObjOneLine >> data.v[2];
					positions.push_back(data);
					printf("position:%f, %f, %f\n", data.v[0], data.v[1], data.v[2]);
				}
				break;
			case 'f':
				printf("face:%s\n", onlineContent);
				break;
			default:
				break;
			}
		}
	}

	DEL_PTR(pFileContent);

}


LH_NAMESPACE_END