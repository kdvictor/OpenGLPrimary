#include "context/skybox.h"

LH_NAMESPACE_BEGIN

void SkyBox::Init(const char* pImagePath)
{
	char temp[128] = { 0 };
	strcpy(temp, pImagePath);
	strcat(temp, "/front.bmp");
	mFront = Texture::LoadTextures(temp);

	memset(temp, 0, 128 * sizeof(char));
	strcpy(temp, pImagePath);
	strcat(temp, "/back.bmp");
	mBack = Texture::LoadTextures(temp);

	memset(temp, 0, 128 * sizeof(char));
	strcpy(temp, pImagePath);
	strcat(temp, "/right.bmp");
	mRight = Texture::LoadTextures(temp);

	memset(temp, 0, 128 * sizeof(char));
	strcpy(temp, pImagePath);
	strcat(temp, "/left.bmp");
	mLeft = Texture::LoadTextures(temp);

	memset(temp, 0, 128 * sizeof(char));
	strcpy(temp, pImagePath);
	strcat(temp, "/top.bmp");
	mTop = Texture::LoadTextures(temp);

	memset(temp, 0, 128 * sizeof(char));
	strcpy(temp, pImagePath);
	strcat(temp, "/bottom.bmp");
	mBottom = Texture::LoadTextures(temp);
}


LH_NAMESPACE_END