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


	mDisplayList.Init([&]() ->void {
		//front
		glBindTexture(GL_TEXTURE_2D, mFront->mTextureId);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); //纹理坐标
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glEnd();

		//left
		glBindTexture(GL_TEXTURE_2D, mLeft->mTextureId);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0); //纹理坐标
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glTexCoord2f(1.0, 0.0);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0, 1.0);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glTexCoord2f(0.0, 1.0);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();


	});
}


LH_NAMESPACE_END