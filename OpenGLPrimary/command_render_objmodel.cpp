#include "command/command_render_objmodel.h"


LH_NAMESPACE_BEGIN

void RenderObjModelCommand::Render()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT, GL_LINE); //线框模式
	//旋转角度
	//static float angle = 0.0;
	//if (angle > 360)
	//{
	//	angle = 0.0f;
	//}
	//angle += 0.2f;
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f); //???
	//glRotatef(angle, 0.0f, 1.0f, 0.0f);
	//glScalef(0.01f, 0.01f, 0.01f); //缩放
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTexture.mTextureId);
	/**************光照***************/
	float blackColor[] = { 0.0f,0.0f,0.0f,1.0f };
	float whiteColor[] = { 1.0f,1.0f,1.0f,1.0f };
	float lightPos[] = { 0.0f,1.0f,0.0f,0.0f }; //齐次坐标，最后一位为0表示向量，无穷远处
	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); //设置光源位置

	float blakMat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float ambientMat[] = { 0.1f, 0.1f, 0.1f, 1.0f }; //环境光
	float diffuseMat[] = { 0.4f, 0.4f, 0.4f, 1.0f }; //漫反射光
	float specularMat[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //镜面射光
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat); //设置材质
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
	//glMaterialf(GL_FRONT, GL_SHININESS, 60.0F); //可以设置光斑,数值越大，光斑越小

	glEnable(GL_LIGHTING); //开启光照
	glEnable(GL_LIGHT0); //设置光源
	/***************************************/


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
	mTexture.Init("./res/earth.bmp");
}

LH_NAMESPACE_END