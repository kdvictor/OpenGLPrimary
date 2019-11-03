#include "command/command_render_pan_rotate_zoom_matrix_light.h"

LH_NAMESPACE_BEGIN

void RenderPanRotateZoomMatrixLightCommand::Render()
{
	///*****************平移，旋转，缩放*******************/
	////glLoadIdentity(); //保证每次进来都是单位矩阵
	//glPushMatrix();
	////glScalef(2.0f, 2.0f, 0.5f); //缩放
	//glTranslatef(2.0f, -2.0f, 0.0f);
	//glRotatef(30, 0.0f, 0.0f, 1.0f);//右手螺旋，大拇指指向自己，握拳方向即是旋转方向
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);
	//glVertex3f(0.0f, 1.0f, -20.0f);

	//glColor4ub(0, 255, 0, 255);
	//glVertex3f(-1.0f, 0.0f, -20.0f);

	//glColor4ub(0, 0, 255, 255);
	//glVertex3f(1.0f, 0.0f, -20.0f);
	//glEnd();
	//glPopMatrix();


	/*****************光照*******************/
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	glEnable(GL_LIGHTING); //开启光照
	glEnable(GL_LIGHT0); //设置光源
	//glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0); //发法线，和漫反射相关
	glVertex3f(-1.0f, -0.5f, -2.0f);

	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0f, -0.5f, -2.0f);


	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, -0.5f, -10.0f);
	glEnd();
	glPopMatrix();
}

LH_NAMESPACE_END