#pragma once
#include "vertexdata.h"

class ObjModel
{
public:
	void Init(const char* const& pFilePath);

	void Draw();

public:
	VertexData* mVertexes;
	int* mIndices;
	int mIndexCount;
};
