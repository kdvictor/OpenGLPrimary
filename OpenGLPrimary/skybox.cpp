#include "context/skybox.h"

LH_NAMESPACE_BEGIN

void SkyBox::Init(const char* pImagePath)
{
	char temp[128] = { 0 };
	strcpy(temp, pImagePath);
	strcat(temp, "/front.bmp");
	mFront = Texture::LoadTextures(temp);
}


LH_NAMESPACE_END