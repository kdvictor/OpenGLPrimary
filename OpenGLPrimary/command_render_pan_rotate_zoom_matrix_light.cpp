#include "command/command_render_pan_rotate_zoom_matrix_light.h"

LH_NAMESPACE_BEGIN

void RenderPanRotateZoomMatrixLightCommand::Render()
{
	/*****************平移，旋转，缩放*******************/
	//glLoadIdentity(); //保证每次进来都是单位矩阵
	////glScalef(2.0f, 2.0f, 0.5f); //缩放
	//glRotatef(30, 0.0f, 0.0f, 1.0f);//右手螺旋，大拇指指向自己，握拳方向即是旋转方向
	//glTranslatef(2.0f, -2.0f, 0.0f);
	//glBegin(GL_TRIANGLES);
	//glColor4ub(255, 0, 0, 255);
	//glVertex3f(0.0f, 1.0f, -20.0f);

	//glColor4ub(0, 255, 0, 255);
	//glVertex3f(-1.0f, 0.0f, -20.0f);

	//glColor4ub(0, 0, 255, 255);
	//glVertex3f(1.0f, 0.0f, -20.0f);
	//glEnd();
}

LH_NAMESPACE_END