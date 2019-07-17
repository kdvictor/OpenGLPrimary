#include "command/command_render_line.h"

LH_NAMESPACE_BEGIN

void RenderLineCommand::Render()
{
	glLineWidth(4.0f); //设置线宽
	glBegin(GL_LINES); //每两个点组成一条线
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(-3.0f, 0.0f, -10.0f);

	glVertex3f(-3.0f, 0.0f, -10.0f);
	glVertex3f(-3.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END