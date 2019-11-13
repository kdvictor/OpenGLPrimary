#include "command/command_render_skybox.h"
#include "common_macrosh.h"


LH_NAMESPACE_BEGIN

RenderSkyBoxCommand::~RenderSkyBoxCommand()
{
	DEL_PTR(mSkyBox);
}

void RenderSkyBoxCommand::Render()
{
	glDisable(GL_LIGHTING);
	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST); //什么是深度测试：深度信息，可以遮挡像素点。离相机越近，深度值越小，反之越大。glDisable(GL_DEPTH_TEST)：以后深度值不会改变
	glPushMatrix();
	glTranslatef(mX, mY, mZ); //让天空盒跟着摄像机，使地球不逃离天空盒

	//front
	glBindTexture(GL_TEXTURE_2D, mSkyBox->mFront->mTextureId);
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

	//back
	glBindTexture(GL_TEXTURE_2D, mSkyBox->mLeft->mTextureId);
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



	glPopMatrix();
}

void RenderSkyBoxCommand::Init_i()
{
	mSkyBox = new SkyBox();
	mSkyBox->Init("res/skybox");
}

LH_NAMESPACE_END