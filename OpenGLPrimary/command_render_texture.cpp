#include "command/command_render_texture.h"

LH_NAMESPACE_BEGIN

void RenderTextureCommand::Render()
{
	this->InitTexture_i();

	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture.mTextureId);

	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -0.5f, -2.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -0.5f, -2.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, -0.5f, -10.0f);
	glEnd();
	glPopMatrix();
}

void RenderTextureCommand::InitTexture_i()
{
	mTexture.Init("test.bmp");
}

LH_NAMESPACE_END