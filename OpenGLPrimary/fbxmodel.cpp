#include "context/fbxmodel.h"
#include <stdlib.h>

LH_NAMESPACE_BEGIN

void FBXModel::GetMaterialPath_i(char* filePath)
{
	memset(filePath + strlen(filePath) - 4, 0, 4);
	strcat(filePath, ".fbm/");
}

void FBXModel::ImportPositions_i(FbxGeometryBase* geometry, std::vector<Vector3f>& positions)
{
	int controlPointCount = geometry->GetControlPointsCount();
	positions.resize(controlPointCount);
	FbxVector4*controlPoints = geometry->GetControlPoints();
	for (int i = 0; i < controlPointCount; ++i)
	{
		positions[i].x = static_cast<float>(controlPoints[i].mData[0]);
		positions[i].y = static_cast<float>(controlPoints[i].mData[1]);
		positions[i].z = static_cast<float>(controlPoints[i].mData[2]);
	}
}

void FBXModel::ImportMesh(FbxMesh* mesh)
{
	std::vector<Vector3f> positions;
	ImportPositions_i(mesh, positions);
	//indices
	int polygonCount = mesh->GetPolygonCount();//triangle count

	FbxStringList uvSetNames;
	mesh->GetUVSetNames(uvSetNames);

	int polygonIndexCount = 0;
	for (int i = 0; i < polygonCount; ++i)
	{
		polygonIndexCount += mesh->GetPolygonSize(i);
	}

	//indices
	FbxLayerElementArrayTemplate<int>*pMaterialIndices;
	mesh->GetMaterialIndices(&pMaterialIndices);
	FbxGeometryElement::EMappingMode mode = mesh->GetElementMaterial()->GetMappingMode();
	mIndices.resize(mMaterials.size());
	switch (mode)
	{
	case fbxsdk::FbxLayerElement::eNone:
		break;
	case fbxsdk::FbxLayerElement::eByControlPoint:
		break;
	case fbxsdk::FbxLayerElement::eByPolygonVertex:
		break;
	case fbxsdk::FbxLayerElement::eByPolygon:
	{
		for (int i = 0; i < polygonCount; ++i)
		{
			//
			int materialIndex = pMaterialIndices->GetAt(i);
			int materialRef = mMaterialIndexes[materialIndex];
			mIndices[materialRef].push_back(i * 3);
			mIndices[materialRef].push_back(i * 3 + 1);
			mIndices[materialRef].push_back(i * 3 + 2);
		}
	}
	break;
	case fbxsdk::FbxLayerElement::eByEdge:
		break;
	case fbxsdk::FbxLayerElement::eAllSame:
		break;
	}

	mVertexs = new VertexData[polygonIndexCount];
	int currentVerticeIndex = 0;
	for (int i = 0; i < polygonCount; ++i)
	{
		int currentPolygonIndexCount = mesh->GetPolygonSize(i);//3
		for (int j = 0; j < currentPolygonIndexCount; ++j)
		{
			int vertexIndex = mesh->GetPolygonVertex(i, j);
			//fbx positions -> our position
			mVertexs[currentVerticeIndex].mPosition[0] = positions[vertexIndex].x;
			mVertexs[currentVerticeIndex].mPosition[1] = positions[vertexIndex].y;
			mVertexs[currentVerticeIndex].mPosition[2] = positions[vertexIndex].z;

			//pos,normal,texcoord
			FbxVector4 normal;
			if (mesh->GetPolygonVertexNormal(i, j, normal))
			{
				//fbx normal -> our normal
				mVertexs[currentVerticeIndex].mNormal[0] = static_cast<float>(normal.mData[0]);
				mVertexs[currentVerticeIndex].mNormal[1] = static_cast<float>(normal.mData[1]);
				mVertexs[currentVerticeIndex].mNormal[2] = static_cast<float>(normal.mData[2]);
			}

			FbxVector2 uv;
			bool bFlag = true;
			if (mesh->GetPolygonVertexUV(i, j, uvSetNames.GetItemAt(0)->mString.Buffer(), uv, bFlag))
			{
				//fbx texcoord -> our texcoord
				mVertexs[currentVerticeIndex].mTexcoord[0] = static_cast<float>(uv.mData[0]);
				mVertexs[currentVerticeIndex].mTexcoord[1] = static_cast<float>(uv.mData[1]);
			}
			currentVerticeIndex++;
		}
	}
}

void FBXModel::ImportMaterial(FbxNode* node)
{
	char szFBXTextureDir[256] = { 0 };
	strcpy(szFBXTextureDir, mFBXPath);
	GetMaterialPath_i(szFBXTextureDir); //ÎÆÀíÍ¼Æ¬Â·¾¶

	int materialCount = node->GetMaterialCount();
	FbxProperty property;
	int nType = 0;
	for (int i = 0; i < materialCount; ++i)
	{
		FbxSurfaceMaterial* surfaceMat = node->GetMaterial(i);
		if (FbxSurfaceLambert::ClassId == surfaceMat->GetClassId())
		{
			nType = 0;
		}
		else if (FbxSurfacePhong::ClassId == surfaceMat->GetClassId())
		{
			nType = 1;
		}
		else
		{
			printf("XXXXX\n");
		}
		property = surfaceMat->FindProperty(FbxLayerElement::sTextureChannelNames[0]); //diffuse texture
		if (property.IsValid())
		{
			int textureCount = property.GetSrcObjectCount<FbxTexture>();
			FbxTexture* texture = property.GetSrcObject<FbxTexture>();
			int currentMaterialIndex = -1;
			if (texture)
			{
				int currentMatCount = mMaterials.size();
				for (int k = 0; k < currentMatCount; ++k)
				{
					if (nType == mMaterials[k]->mType)
					{
						if (strcmp(texture->GetName(), mMaterials[k]->mDiffuseColorTexture) == 0)
						{
							currentMaterialIndex = k;
							break;
						}
					}
				}

				if (currentMaterialIndex == -1)
				{
					Mat* mat = new Mat;
					mat->mType = nType;
					memset(mat->mDiffuseColorTexture, 0, 256);
					strcpy(mat->mDiffuseColorTexture, texture->GetName());
					char temp[256] = { 0 };
					strcpy(temp, szFBXTextureDir);
					strcat(temp, texture->GetName());
					mat->mtexture = Texture::LoadTextures(temp);
					currentMaterialIndex = mMaterials.size();
					mMaterials.push_back(mat);
				}
				mMaterialIndexes.insert(std::make_pair(i, currentMaterialIndex));
			}
		}
	}
}

void FBXModel::ImportNode(FbxNode* node)
{
	//decode per node
	if (node->GetMesh())
	{
		ImportMaterial(node);
		for (auto iter = mMaterials.begin(); iter != mMaterials.end(); ++iter)
		{
			printf("%d %s\n", (*iter)->mType, (*iter)->mDiffuseColorTexture);
		}
		for (auto iter = mMaterialIndexes.begin(); iter != mMaterialIndexes.end(); ++iter)
		{
			printf("mat index %d -> %d\n", iter->first, iter->second);
		}
		ImportMesh(node->GetMesh());
	}
	//decode child
	int nChildNode = node->GetChildCount();
	for (int i = 0; i < nChildNode; ++i)
	{
		ImportNode(node->GetChild(i));
	}
}

void FBXModel::Init(const char* const& filePath)
{
	memset(mFBXPath, 0, 256);
	strcpy(mFBXPath, filePath);
	FbxManager*fbxManager = FbxManager::Create();
	FbxIOSettings*fbxIOSetting = FbxIOSettings::Create(fbxManager, IOSROOT);
	FbxImporter*fbxImporter = FbxImporter::Create(fbxManager, "");
	fbxManager->SetIOSettings(fbxIOSetting);
	if (fbxImporter->Initialize(filePath, -1, fbxManager->GetIOSettings()))
	{
		FbxScene*scene = FbxScene::Create(fbxManager, "");
		fbxImporter->Import(scene);

		FbxNode*rootNode = scene->GetRootNode();
		ImportNode(rootNode);
		scene->Destroy();
	}
	fbxImporter->Destroy();
	fbxIOSetting->Destroy();
	fbxManager->Destroy();
}


void FBXModel::Draw()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glScalef(0.01f, 0.01f, 0.01f);
	for (int i = 0; i < mMaterials.size(); i++)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.01F);
		glBindTexture(GL_TEXTURE_2D, mMaterials[i]->mtexture->mTextureId);
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < mIndices[i].size(); ++j)
		{
			glTexCoord2fv(mVertexs[mIndices[i][j]].mTexcoord);
			glVertex3fv(mVertexs[mIndices[i][j]].mPosition);
		}
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_ALPHA_TEST);
}


LH_NAMESPACE_END