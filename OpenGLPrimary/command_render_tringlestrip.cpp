#include "command/command_render_tringlestrip.h"

LH_NAMESPACE_BEGIN

void RenderTringleStripCommand::Render()
{
	glBegin(GL_TRIANGLE_STRIP); //ÆæÊý£º1-2-3.Å¼Êýµã£º3-2-4
	glColor4ub(255.0, 0.0, 0.0, 255.0);
	glVertex3f(0.0f, 0.0f, -10.0f); 
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -2.0f, -10.0f);

	glColor4ub(255.0, 0.0, 0.0, 255.0);
	glVertex3f(3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(3.0f - 3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(3.0f - 3.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END