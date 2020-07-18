#include "imagesprite.h"

void ImageSprite::SetTexture(Texture * texture)
{
	mTexture = texture;
}

void ImageSprite::SetRect(const float & centerX, const float & centerY, const float & width, const float & height)
{
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	mMesh[0].x = centerX - halfWidth;
	mMesh[0].y = centerY + halfHeight;
	mMesh[1].x = centerX - halfWidth;
	mMesh[1].y = centerY - halfHeight;
	mMesh[2].x = centerX + halfWidth;
	mMesh[2].y = centerY - halfHeight;
	mMesh[3].x = centerX + halfWidth;
	mMesh[3].y = centerY + halfHeight;
}

void ImageSprite::Draw()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, mTexture->mTextureId);
	//glEnable(GL_ALPHA_TEST); //alpha test
	//glAlphaFunc(GL_GREATER, 0.1); //透明度> 0.1才画出来
	//混合
	glEnable(GL_BLEND);
	//dst = src*alpha(src.alpha) + dst*alpha(1 -(src.alpha) )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex3fv(mMesh[0].v);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(mMesh[1].v);
	glTexCoord2f(1.0, 0.0);
	glVertex3fv(mMesh[2].v);
	glTexCoord2f(1.0, 1.0);
	glVertex3fv(mMesh[3].v);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glPopMatrix();
}
