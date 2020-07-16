#include "skybox.h"

void SkyBox::Init(const char * const & pFolderPath)
{
	char filePath[128];
	memset(filePath, 0, 128 * sizeof(char));
	//front
	std::strcat(filePath, pFolderPath);
	std::strcat(filePath, "/front.bmp");
	mFront = Texture::LoadTexture(filePath);
	mFront->mFilePath = filePath;
	//back
	memset(filePath, 0, 128 * sizeof(char));

}

void SkyBox::Draw(const int& x, const int& y, const int& z)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST); //深度最远
	glPushMatrix();
	glTranslatef(x, y, z); //跟着摄像机移动

	glBindTexture(GL_TEXTURE_2D, mFront->mTextureId);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}
