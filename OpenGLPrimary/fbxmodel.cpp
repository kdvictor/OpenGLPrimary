#include "context/fbxmodel.h"
#include "fbxsdk.h"


LH_NAMESPACE_BEGIN

void FBXModel::Init(const char* const& filePath)
{
	FbxManager* pFbxManager = FbxManager::Create();
	FbxIOSettings* pFbxSettings = FbxIOSettings::Create(pFbxManager, IOSROOT);
	FbxImporter* PFbxImporter = FbxImporter::Create(pFbxManager, "");
	pFbxManager->SetIOSettings(pFbxSettings);


	PFbxImporter->Destroy();
	pFbxSettings->Destroy();
	pFbxManager->Destroy();
}


void FBXModel::Draw()
{

}


LH_NAMESPACE_END