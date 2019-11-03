#include "command/command_render_tringlefan.h"

LH_NAMESPACE_BEGIN

void RenderTringleFanCommand::Render()
{
	glBegin(GL_TRIANGLE_FAN); //1-2-3,1-3-4,1-4-5....
	glColor4ub(255.0, 0.0, 0.0, 255.0);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-5.0f, -2.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -2.0f, -10.0f);
	glColor4ub(0.0, 66.0, 255.0, 255.0);
	glVertex3f(2.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END