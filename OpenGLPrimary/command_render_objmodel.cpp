#include "command/command_render_objmodel.h"


LH_NAMESPACE_BEGIN

void RenderObjModelCommand::Render()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE); //Ïß¿òÄ£Ê½
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f); //???
	//glRotatef(30, 0.0f, 1.0f, 0.0f);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, mTexture.mTextureId);
	glBegin(GL_TRIANGLES);

	for (int i = 0;  i < mObjModel.mIndicesCount; ++i)
	{
		//glVertex3f(mObjModel.mVertexes[mObjModel.mIndices[i]].mPosition[0], 
		//	mObjModel.mVertexes[mObjModel.mIndices[i]].mPosition[1], 
		//	mObjModel.mVertexes[mObjModel.mIndices[i]].mPosition[2]);
		glTexCoord2fv(mObjModel.mVertexes[mObjModel.mIndices[i]].mTexcoord);
		glNormal3fv(mObjModel.mVertexes[mObjModel.mIndices[i]].mNormal);
		glVertex3fv(mObjModel.mVertexes[mObjModel.mIndices[i]].mPosition);
	}

	glEnd();
	glPopMatrix();
}

void RenderObjModelCommand::Init_i()
{
	mObjModel.Init("./res/Sphere.obj");
	mTexture.Init("./res/test.bmp");
}

LH_NAMESPACE_END