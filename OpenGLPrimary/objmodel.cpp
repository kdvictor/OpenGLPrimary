#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>
#include "context/objmodel.h"
#include "context/context_helper.h"
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN

ObjModel::ObjModel()
{

}

ObjModel::~ObjModel()
{
	DEL_ARRAY(mIndices);
	DEL_ARRAY(mVertexes);
}

void ObjModel::Init(const char* objModel)
{
	unsigned char* pFileContent = ContextHelper::LoadFileContent(objModel);
	//找出有用的信息，V:顶点 Vt:纹理坐标 Vn：法线，f: face 
	std::stringstream ssFileContent((char*)pFileContent);
	char onlineContent[256]; //一行数据
	std::string temp;
	std::vector<ObjOneLineData> positions, texttures, normals;
	std::vector<VerticeDefine> vertexes;//去重之后的所有点
	std::vector<int> indexs; //画图时，点与点之间的信息
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
					ssObjOneLine >> temp; //去掉vt
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					texttures.push_back(data);
				}
				else if(*(onlineContent + 1) == 'n')
				{
					ssObjOneLine >> temp;
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					ssObjOneLine >> data.v[2];
					normals.push_back(data);
				}
				else
				{
					ssObjOneLine >> temp;
					ObjOneLineData data;
					ssObjOneLine >> data.v[0];
					ssObjOneLine >> data.v[1];
					ssObjOneLine >> data.v[2];
					positions.push_back(data);
				}
				break;
			case 'f':
			{
				ssObjOneLine >> temp;
				std::string vertexStr;//: 1/1/1
				for (int i = 0; i < 3; ++i)
				{
					ssObjOneLine >> vertexStr;
					size_t pos1 = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos1);

					size_t pos2 = vertexStr.find_first_of('/', pos1 + 1);
					std::string vtextureIndexStr = vertexStr.substr(pos1 + 1, pos2 - 1 - pos1);

					size_t pos3 = vertexStr.find_first_of('/', pos2 + 1);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length());

					VerticeDefine vertexDefine;
					vertexDefine.posiIndex = atoi(posIndexStr.c_str());
					vertexDefine.texcoordIndex = atoi(vtextureIndexStr.c_str());
					vertexDefine.normalIndex = atoi(normalIndexStr.c_str());

					//去重
					int currentIndex = -1;
					for (int i = 0; i < vertexes.size(); ++i)
					{
						if (vertexes[i].posiIndex == vertexDefine.posiIndex &&
							vertexes[i].texcoordIndex == vertexDefine.texcoordIndex &&
							vertexes[i].normalIndex == vertexDefine.normalIndex)
						{
							currentIndex = i;
							break;
						}
					}


					if (currentIndex == -1)
					{
						currentIndex = vertexes.size();
						vertexes.push_back(vertexDefine);
					}
					indexs.push_back(currentIndex);


				}
				break;
			}
			default:
				break;
			}
		}
	}

	//转成绘制需要的数据
	mIndicesCount = indexs.size();
	mIndices = new int[mIndicesCount];
	memset(mIndices, 0, sizeof(int)*mIndicesCount);
	for (int i = 0; i < mIndicesCount; ++i)
	{
		mIndices[i] = indexs[i];
	}

	mVertexes = new VertexData[vertexes.size()];
	for (int i = 0; i < vertexes.size(); ++i)
	{
		memcpy(mVertexes[i].mPosition, positions[vertexes[i].posiIndex - 1].v, sizeof(float) * 3);
		memcpy(mVertexes[i].mTexcoord, texttures[vertexes[i].texcoordIndex - 1].v, sizeof(float) * 2);
		memcpy(mVertexes[i].mNormal, normals[vertexes[i].normalIndex - 1].v, sizeof(float) * 3);
	}



	DEL_PTR(pFileContent);

}


LH_NAMESPACE_END