#include "command/command_render_line_strip.h"

LH_NAMESPACE_BEGIN

void RenderLineStripCommand::Render()
{
	glLineWidth(4.0f); //设置线宽
	glBegin(GL_LINE_STRIP); //把所有点连起来，不构成一个圈
	glColor4ub(255.0, 0.0, 0.0, 255.0);//设置当前颜色
	glVertex3f(0.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END