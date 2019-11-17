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

	//indices

	//normal

	//textcoord
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