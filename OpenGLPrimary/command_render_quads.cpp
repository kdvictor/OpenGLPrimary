#include "command/command_render_quads.h"

LH_NAMESPACE_BEGIN

void RenderQuadsCommand::Render()
{
	///*****************GL_QUADS***********************/
	//glBegin(GL_QUADS); //每四个点画一个多边形
	//glColor4ub(255.0, 0.0, 0.0, 255.0);
	//glVertex3f(0.0f, 0.0f, -10.0f);
	//glColor4ub(0.0, 255.0, 0.0, 255.0);
	//glVertex3f(-5.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(-3.0f, -3.0f, -10.0f);
	//glColor4ub(0.0, 66.0, 255.0, 255.0);
	//glVertex3f(2.0f, -2.0f, -10.0f);

	//glColor4ub(255.0, 0.0, 0.0, 255.0);
	//glVertex3f(1.0f, 0.0f, -10.0f);
	//glColor4ub(0.0, 255.0, 0.0, 255.0);
	//glVertex3f(1-5.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(1-3.0f, -3.0f, -10.0f);
	//glColor4ub(0.0, 66.0, 255.0, 255.0);
	//glVertex3f(1+2.0f, -2.0f, -10.0f);
	//glEnd();

	///*****************GL_QUAD_STRIP***********************/
	//glBegin(GL_QUAD_STRIP); //1-2-4-3, 3-4-6-5
	//glColor4ub(255.0, 0.0, 0.0, 255.0);
	//glVertex3f(0.0f, 0.0f, -10.0f);
	//glColor4ub(0.0, 255.0, 0.0, 255.0);
	//glVertex3f(-5.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 66.0, 255.0, 255.0);
	//glVertex3f(2.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(-3.0f, -3.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(3.0f, 3.0f, -10.0f);
	//glColor4ub(0.0, 66.0, 255.0, 255.0);
	//glVertex3f(4.0f, -3.0f, -10.0f);
	//glEnd();

	///****************GL_POLYGON************************/
	//glBegin(GL_POLYGON); //依次连接
	//glColor4ub(255.0, 0.0, 0.0, 255.0);
	//glVertex3f(0.0f, 0.0f, -10.0f);
	//glColor4ub(0.0, 255.0, 0.0, 255.0);
	//glVertex3f(-5.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(-3.0f, -3.0f, -10.0f);
	//glColor4ub(0.0, 66.0, 255.0, 255.0);
	//glVertex3f(2.0f, -2.0f, -10.0f);
	//glEnd();

	/*****************线框模式***********************/
	//glPolygonMode(GL_FRONT, GL_LINE);//线框模式

	//glPointSize(20);
	//glPolygonMode(GL_FRONT, GL_POINT);
	//glEnable(GL_POINT_SMOOTH); //将点变圆
	////如果不能变圆，需要启用blend
	//glEnable(GL_BLEND);//我的机子可以变圆

	glBegin(GL_POLYGON); //依次连接
	glColor4ub(255.0, 0.0, 0.0, 255.0);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-4.0f, -2.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -3.0f, -10.0f);
	glColor4ub(0.0, 66.0, 255.0, 255.0);
	glVertex3f(2.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END