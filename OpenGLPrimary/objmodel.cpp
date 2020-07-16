#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <gl/GL.h>
#include "objmodel.h"
#include "utlis.h"

typedef struct FloatData
{
	float v[3];
}FloatData;

typedef struct VertexDefine
{
	int positionIndex;
	int texcoordIndex;
	int normalIndex;
};

void ObjModel::Init(const char * const & pFilePath)
{
	unsigned char* pFileContent = LoadFileContent(pFilePath);
	if (pFileContent == nullptr)
	{
		//日志
	}

	std::stringstream ssFileContent((char*)pFileContent);
	std::string temp;
	char szOneLine[256];
	std::vector<FloatData> positions, normals, texcoords;
	std::vector<VertexDefine> vertexDefines;
	std::vector<int> indexes;

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
					//printf("texcoord:%f,%f\n", data.v[0], data.v[1]);
				}
				else if(szOneLine[1] == 'n')
				{
					ssOneLine >> temp;
					ssOneLine >> data.v[0];
					ssOneLine >> data.v[1];
					ssOneLine >> data.v[2];
					normals.push_back(data);
					//printf("normal:%f,%f,%f\n", data.v[0], data.v[1],data.v[2]);
				}
				else
				{
					ssOneLine >> temp;
					ssOneLine >> data.v[0];
					ssOneLine >> data.v[1];
					ssOneLine >> data.v[2];
					positions.push_back(data);
					//printf("position:%f,%f,%f\n", data.v[0], data.v[1], data.v[2]);
				}
			}
			else if (szOneLine[0] == 'f')
			{
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexString;
				for (int i = 0; i < 3; ++i)
				{
					ssOneLine >> vertexString;
					int pos = vertexString.find_first_of('/');
					std::string positionIndex = vertexString.substr(0, pos);
					int pos2 = vertexString.find_first_of('/', pos+1);
					std::string texcoordIndex = vertexString.substr(pos + 1, pos2 - pos - 1);
					std::string normalIndex = vertexString.substr(pos2 + 1, vertexString.length() - pos2 - 1);
					//printf("%s,%s,%s\n", positionIndex.c_str(), texcoordIndex.c_str(), normalIndex.c_str());
					VertexDefine vd;
					vd.positionIndex = atoi(positionIndex.c_str());
					vd.texcoordIndex = atoi(texcoordIndex.c_str());
					vd.normalIndex = atoi(normalIndex.c_str());

					int currentVertexIndex = -1;
					for (int i = 0; i < vertexDefines.size(); ++i)
					{
						if (vertexDefines[i].positionIndex == vd.positionIndex && 
							vertexDefines[i].texcoordIndex == vd.texcoordIndex &&
							vertexDefines[i].normalIndex == vd.normalIndex)
						{
							currentVertexIndex = i;
							break;
						}
					}

					//没有找到重复点
					if (-1 == currentVertexIndex)
					{
						vertexDefines.push_back(vd);
						currentVertexIndex = vertexDefines.size() - 1;
					}

					indexes.push_back(currentVertexIndex);
				}
			}
		}
	}

	//生成数据
	mIndexCount = indexes.size();
	mIndices = new int[mIndexCount];
	for (int i = 0; i < mIndexCount; ++i)
	{
		mIndices[i] = indexes[i];
		//printf("%d\n", mIndices[i]);
	}

	int vertexCount = vertexDefines.size();
	mVertexes = new VertexData[vertexCount];
	for (int i = 0; i < vertexCount; ++i)
	{
		memcpy(mVertexes[i].position, positions[vertexDefines[i].positionIndex - 1].v, 3 * sizeof(float));
		memcpy(mVertexes[i].texcoord, texcoords[vertexDefines[i].texcoordIndex - 1].v, 2 * sizeof(float));
		memcpy(mVertexes[i].normal, normals[vertexDefines[i].normalIndex - 1].v, 3 * sizeof(float));
	}
}

void ObjModel::Draw()
{
	static float angle = 0.0f;
	angle += 0.1;
	if (angle > 360.0)
	{
		angle = 0.0f;
	}
	//glPolygonMode(GL_FRONT, GL_LINE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -3.0f); //移动一下，不然看不见
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < mIndexCount; ++i)
	{
		glTexCoord2fv(mVertexes[mIndices[i]].texcoord);
		glNormal3fv(mVertexes[mIndices[i]].normal);
		glVertex3f(mVertexes[mIndices[i]].position[0], mVertexes[mIndices[i]].position[1], mVertexes[mIndices[i]].position[2]);
	}

	glEnd();
	glPopMatrix();
}
