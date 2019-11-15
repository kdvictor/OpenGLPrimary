#include "context/image_sprite.h"


LH_NAMESPACE_BEGIN

void ImageSprite::SetTexture(Texture* const& texture)
{
	mTexture = texture;
}

void ImageSprite::SetRect(const float& x, const float& y, const float& width, const float& height)
{
	auto halfWidth = width / 2;
	auto halfHeight = height / 2;

	mMesh[0].x = x - halfWidth;
	mMesh[0].y = y - halfHeight;

	mMesh[1].x = x + halfWidth;
	mMesh[1].y = y - halfHeight;

	mMesh[2].x = x + halfWidth;
	mMesh[2].y = y + halfHeight;

	mMesh[3].x = x - halfWidth;
	mMesh[3].y = y + halfHeight;
}

void ImageSprite::Draw()
{
	glEnable(GL_TEXTURE_2D);
	//去掉头像边框，一般是ALPHA通道造成，开启alpha测试或者使用混合
	glDisable(GL_LIGHTING);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_GREATER, 0.1f); //<0.1不让画
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA/*源：当前的图像*/, GL_ONE_MINUS_SRC_ALPHA/*目的：已经存在的图像*/);
	//混合：dst = src.apha*salpha + dst.alpha*dalpha;
	//GL_SRC_ALPHA:salpha = src.alpha
	//GL_ONE_MINUS_SRC_ALPHA: dalpha = 1-src.alpha


	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, mTexture->mTextureId);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(mMesh[0].v); //3f与3fv

	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(mMesh[1].v);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(mMesh[2].v);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(mMesh[3].v);

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
}

LH_NAMESPACE_END