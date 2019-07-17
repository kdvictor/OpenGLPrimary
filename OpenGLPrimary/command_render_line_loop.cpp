#include "command/command_render_line_loop.h"

LH_NAMESPACE_BEGIN

void RenderLineLoopCommand::Render()
{
	glLineWidth(4.0f); //设置线宽
	glBegin(GL_LINE_LOOP); //把所有点连成一个圈
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(-3.0f, 0.0f, -10.0f);
	glVertex3f(-3.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END