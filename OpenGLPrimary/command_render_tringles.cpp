#include "command/command_render_tringles.h"

LH_NAMESPACE_BEGIN

void RenderTringlesCommand::Render()
{
	glBegin(GL_TRIANGLES); //默认逆时针方向（ccw:contour clock wise）
	glColor4ub(255.0, 0.0, 0.0, 255.0);//设置当前颜色
	glVertex3f(0.0f, 0.0f, -10.0f); //每三个点组成一个三角形，可以画多个三角形
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -2.0f, -10.0f);

	glColor4ub(255.0, 0.0, 0.0, 255.0);
	glVertex3f(3.0f, 0.0f, -10.0f); 
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(3.0f-3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(3.0f-3.0f, -2.0f, -10.0f);
	glEnd();

	////交换两个点使其变成CW
	//glEnable(GL_CULL_FACE); //只显示正面（CW），可以提高效率，不用绘制两个面
	//glFrontFace(GL_CW); //可以将默认正面改成CW方向
	//glBegin(GL_TRIANGLES); 
	//glColor4ub(255.0, 0.0, 0.0, 255.0);
	//glVertex3f(0.0f, 0.0f, -10.0f);
	//glColor4ub(0.0, 0.0, 255.0, 255.0);
	//glVertex3f(-3.0f, -2.0f, -10.0f);
	//glColor4ub(0.0, 255.0, 0.0, 255.0);
	//glVertex3f(-3.0f, 0.0f, -10.0f);
	//glEnd();
}

LH_NAMESPACE_END