#include "context/fbxmodel.h"

LH_NAMESPACE_BEGIN

void FBXModel::ImportPositions_i(FbxGeometryBase* geometry, std::vector<Vector3f>& positions)
{
	int controlPointCount = geometry->GetControlPointsCount();
	positions.resize(controlPointCount);
	FbxVector4* controlPoints = geometry->GetControlPoints();

	for (int i = 0; i < controlPointCount; ++i)
	{
		positions[i].x = controlPoints[i].mData[0];
		positions[i].y = controlPoints[i].mData[1];
		positions[i].z = controlPoints[i].mData[2];
		printf("%f,%f,%f\n", positions[i].x, positions[i].y, positions[i].z);
	}
}

void FBXModel::ImportMesh(FbxMesh* mesh)
{
	std::vector<Vector3f> positions;
	ImportPositions_i(mesh, positions);

	int polygonCount = mesh->GetPolygonCount(); //三角形个数

	FbxStringList uvSetNames;
	mesh->GetUVSetNames(uvSetNames);

	for (int i = 0; i < polygonCount; ++i)
	{
		int currentPolygonIndexCount = mesh->GetPolygonSize(i); //3(三角形)

		for (int j = 0; j < currentPolygonIndexCount; ++j)
		{
			int vertexIndex = mesh->GetPolygonVertex(i, j);
			//fbx position -> our position
			printf("%f,%f,%f\n", positions[vertexIndex].x, positions[vertexIndex].y, positions[vertexIndex].z);

			//fbx normal -> our normal
			FbxVector4 normal;
			if (mesh->GetPolygonVertexNormal(i, j, normal))
			{
				printf("%f,%f,%f\n", normal.mData[0], normal.mData[1], normal.mData[1]);
			}

			//fbx texcoord -> our texcoord
			FbxVector2 uv;
			bool bFlag = true;
			if (mesh->GetPolygonVertexUV(i, j, uvSetNames.GetItemAt(0)->mString.Buffer(),uv, bFlag));
			{
				printf("%f, %f\n", uv.mData[0], uv.mData[1]);
			}
		}

	}
}

void FBXModel::ImportMaterial(FbxNode* node)
{

}

void FBXModel::ImportNode(FbxNode* node)
{
	printf("%s\n", node->GetName());
	if (node->GetMesh())
	{
		printf("%s\n", node->GetMesh()->GetName());
		ImportMaterial(node);
		ImportMesh(node->GetMesh());
	}

	int nChildNode = node->GetChildCount();
	for (int i = 0; i < nChildNode; ++i)
	{
		ImportNode(node->GetChild(i));
	}
}

void FBXModel::Init(const char* const& filePath)
{
	FbxManager* pFbxManager = FbxManager::Create();
	FbxIOSettings* pFbxSettings = FbxIOSettings::Create(pFbxManager, IOSROOT);
	FbxImporter* PFbxImporter = FbxImporter::Create(pFbxManager, "");
	pFbxManager->SetIOSettings(pFbxSettings);

	if (PFbxImporter->Initialize(filePath, -1, pFbxManager->GetIOSettings()))
	{
		FbxScene* scene = FbxScene::Create(pFbxManager, "");
		PFbxImporter->Import(scene);

		FbxNode* rootNode = scene->GetRootNode();
		ImportNode(rootNode);
		scene->Destroy();
	}


	PFbxImporter->Destroy();
	pFbxSettings->Destroy();
	pFbxManager->Destroy();
}


void FBXModel::Draw()
{

}


LH_NAMESPACE_END